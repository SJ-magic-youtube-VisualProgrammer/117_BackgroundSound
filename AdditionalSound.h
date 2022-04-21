/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sj_common.h"
#include "ofxNoncopyable.h"


/************************************************************
************************************************************/
class ADDITIONAL_SOUND : private ofx__NON_COPYABLE{
private:
	/****************************************
	****************************************/
	enum STATE{
		STATE__WAIT,
		STATE__KICKSOUND,
	};
	
	/****************************************
	****************************************/
	int id_of_this_object = 0;
	
	string dirname = "../../../data/sound/";
	
	STATE State = STATE__WAIT;
	
	float t_interval;
	int id = -1;
	float t_LastSound = 0;
	
	const float d_INTERVAL_MIN = 3.0f;
	const float d_INTERVAL_MAX = 12.0f;
	
	
	vector<int> order;
	
	vector<ofSoundPlayer*> Sounds;
	vector<string*> SoundFileNames;
	
	/****************************************
	****************************************/
	void set_dir(const string& _dirname);
	void makeup_music_table();
	void load_music_table();
	void prep_NextSoundInfo();
	void shuffle(vector<int>& data);
	
	void init_order();
	void StateChart();
	
public:
	/****************************************
	****************************************/
	ADDITIONAL_SOUND();
	~ADDITIONAL_SOUND();
	void setup(int _id_of_this_object, const string& _dirname);
	void update();
	float get_timeLeft_to_next_kick();
	int get_Next_id();
};


