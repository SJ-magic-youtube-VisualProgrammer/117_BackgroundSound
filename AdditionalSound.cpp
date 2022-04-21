/************************************************************
************************************************************/
#include "AdditionalSound.h"

/* for dir search */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h> 
#include <dirent.h>
#include <string>

// using namespace std;

/************************************************************
************************************************************/

/******************************
******************************/
ADDITIONAL_SOUND::ADDITIONAL_SOUND(){
}

/******************************
******************************/
ADDITIONAL_SOUND::~ADDITIONAL_SOUND(){
	/********************
	********************/
	for(int i = 0; i < Sounds.size(); i++){
		delete Sounds[i];
	}
	
	for(int i = 0; i < SoundFileNames.size(); i++){
		delete SoundFileNames[i];
	}
}

/******************************
******************************/
void ADDITIONAL_SOUND::setup(int _id_of_this_object, const string& _dirname){
	/********************
	********************/
	id_of_this_object = _id_of_this_object;
	set_dir(_dirname);
	
	/********************
	********************/
	makeup_music_table();
	load_music_table();
	
	/********************
	********************/
	init_order();
	
	prep_NextSoundInfo();
}


/******************************
******************************/
void ADDITIONAL_SOUND::set_dir(const string& _dirname)
{
	dirname = _dirname;
}

/******************************
******************************/
void ADDITIONAL_SOUND::init_order()
{
	order.resize(Sounds.size());
	
	for(int i = 0; i < order.size(); i++){
		order[i] = i;
	}
}

/******************************
******************************/
void ADDITIONAL_SOUND::makeup_music_table()
{
	/********************
	********************/
	DIR *pDir;
	struct dirent *pEnt;
	struct stat wStat;
	string wPathName;

	pDir = opendir( dirname.c_str() );
	if ( NULL == pDir ) { ERROR_MSG(); std::exit(1); }
	
	pEnt = readdir( pDir );
	while ( pEnt ) {
		// .と..は処理しない
		if ( strcmp( pEnt->d_name, "." ) && strcmp( pEnt->d_name, ".." ) ) {
		
			// wPathName = dirname + "/" + pEnt->d_name;
			wPathName = dirname + pEnt->d_name;
			
			// ファイルの情報を取得
			if ( stat( wPathName.c_str(), &wStat ) ) {
				printf( "Failed to get stat %s \n", wPathName.c_str() );
				fflush(stdout);
				break;
			}
			
			if ( S_ISDIR( wStat.st_mode ) ) {
				// nothing.
			} else {
			
				vector<string> str = ofSplitString(pEnt->d_name, ".");
				if(str[str.size()-1] == "mp3"){
					// string str_NewFileName = wPathName;
					// string str_NewFileName = pEnt->d_name;
					string* str_NewFileName = new string(pEnt->d_name);
					
					SoundFileNames.push_back(str_NewFileName);
				}
			}
		}
		
		pEnt = readdir( pDir ); // 次のファイルを検索する
	}

	closedir( pDir );
	
	/********************
	********************/
	if(SoundFileNames.size() == 0){
		ERROR_MSG();
		std::exit(1);
	}
 }

/******************************
******************************/
void ADDITIONAL_SOUND::load_music_table()
{
	/********************
	********************/
	if(SoundFileNames.size() <= 0)	return;

	/********************
	********************/
	printf("> load Sound Files\n");
	Sounds.resize(SoundFileNames.size());
	for(int i = 0; i < Sounds.size(); i++){
		Sounds[i] = new ofSoundPlayer;
		
		Sounds[i]->loadSound(dirname + SoundFileNames[i]->c_str());
		Sounds[i]->setLoop(false);
		Sounds[i]->setMultiPlay(true);
		Sounds[i]->setVolume(1.0);
		
		printf("%3d:%s\n", i, SoundFileNames[i]->c_str());
	}
	printf("--------------------\n");
	fflush(stdout);
}

/******************************
******************************/
void ADDITIONAL_SOUND::prep_NextSoundInfo()
{
	t_interval = ofRandom(d_INTERVAL_MIN, d_INTERVAL_MAX);
	
	id++;
	if(Sounds.size() <= id) { id = 0; printf("Table of %d Loop\n", id_of_this_object); fflush(stdout); }
	
	if(id == 0)	shuffle(order); // 1st or Loop
	
	/*
	int LastId = id;
	id = int ( ((double)rand() / ((double)RAND_MAX + 1)) * Sounds.size() );
	if(Sounds.size() <= id){
		WARNING_MSG();
		id = 0;
	}
	if(id == LastId){
		id++;
		if(Sounds.size() <= id) id = 0;
	}
	*/
}

/******************************
description
	fisher yates法
	偏りをなくすため、回を追うごとに乱数範囲を狭めていくのがコツ
	http://www.fumiononaka.com/TechNotes/Flash/FN0212003.html
******************************/
void ADDITIONAL_SOUND::shuffle(vector<int>& data)
{
	// int i = data.size();
	// while(i--){
	// while(--i){
	
	for(int i = data.size() - 1; 0 < i; i--){
		/********************
		int j = rand() % (i + 1);
		********************/
		int j = (int)( ((double)rand() / ((double)RAND_MAX + 1)) * (i + 1) );
		
		/********************
		********************/
		int temp = data[i];
		data[i] = data[j];
		data[j] = temp;
	}
}

/******************************
******************************/
void ADDITIONAL_SOUND::update(){
	StateChart();
}

/******************************
******************************/
void ADDITIONAL_SOUND::StateChart(){
	float now = float(ofGetElapsedTimeMillis()) / 1000.0f;
	
	switch(State){
		case STATE__WAIT:
			if(t_interval < now - t_LastSound){
				State = STATE__KICKSOUND;
			}
			break;
			
		case STATE__KICKSOUND:
			State = STATE__WAIT;
			
			if( Sounds[order[id]]->isLoaded() )	 Sounds[order[id]]->play();
			t_LastSound = now;
			
			prep_NextSoundInfo();
			break;
	}
}

/******************************
******************************/
int ADDITIONAL_SOUND::get_Next_id(){
	return order[id];
}

/******************************
******************************/
float ADDITIONAL_SOUND::get_timeLeft_to_next_kick(){
	float now = float(ofGetElapsedTimeMillis()) / 1000.0f;
	return  t_interval - (now - t_LastSound);
}

