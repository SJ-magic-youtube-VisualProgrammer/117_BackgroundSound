/************************************************************
************************************************************/
#include "ofApp.h"

#include <time.h>

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(){
	font.load("font/RictyDiminished-Regular.ttf", 20/* font size in pixels */, true/* _bAntiAliased */, true/* _bFullCharacterSet */, false/* makeContours */, 0.3f/* simplifyAmt */, 72/* dpi */);
}

/******************************
******************************/
ofApp::~ofApp(){
}

/******************************
******************************/
void ofApp::exit(){

}

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	srand((unsigned int)time(NULL));
	
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("AmbientSound");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	setup_Gui();
	
	load_and_start_backMusic();
	
	for(int i = 0; i < NUM_ADDITIONAL_DIR; i++){
		char buf[BUF_SIZE_S];
		sprintf(buf, "../../../data/sound/front[%d]/", i);
		
		AdditionalSound[i].setup(i, buf);
	}
	
}

/******************************
description
	memoryを確保は、app start後にしないと、
	segmentation faultになってしまった。
******************************/
void ofApp::setup_Gui()
{
	/********************
	********************/
	Gui_Global = new GUI_GLOBAL;
	Gui_Global->setup("param", "gui.xml", 10, 10);
}

/******************************
******************************/
void ofApp::load_and_start_backMusic()
{
	/********************
	load時間短縮のため、mp3->wav としておくこと : ffmpeg
		https://qiita.com/suzutsuki0220/items/43c87488b4684d3d15f6
		> ffmpeg -i "input.mp3" -vn -ac 2 -ar 44100 -acodec pcm_s16le -f wav "output.wav"
	********************/
	backSound.loadSound("sound/back/back.wav", true/* streaming */);
	if(!backSound.isLoaded()) { ERROR_MSG(); std::exit(1); }
	
	/********************
	********************/
	backSound.setLoop(true);
	backSound.setMultiPlay(true);
	backSound.setVolume(Gui_Global->BackSound_vol);
	
	backSound.play();
}

/******************************
******************************/
void ofApp::update(){
	/********************
	********************/
	ofSoundUpdate();
	
	/********************
	********************/
	if(backSound.getVolume() != Gui_Global->BackSound_vol)	backSound.setVolume(Gui_Global->BackSound_vol);
	
	/********************
	********************/
	for(int i = 0; i < NUM_ADDITIONAL_DIR; i++){
		AdditionalSound[i].update();
	}

}

/******************************
******************************/
void ofApp::draw(){
	/********************
	********************/
	ofVec2f ofs[2] = { // NUM_ADDITIONAL_DIR にしないこと : segmentation fault when NUM_ADDITIONAL_DIR = 1.
		ofVec2f(51, 127),
		ofVec2f(51, 180),
	};
	
	/********************
	********************/
	ofBackground(30);
	ofSetColor(255);
	
	/********************
	********************/
	char buf[BUF_SIZE_S];
	
	sprintf(buf, "pos of Base sound : %5.3f", backSound.getPosition());
	font.drawString(buf, 51, 77);
	
	for(int i = 0; i < NUM_ADDITIONAL_DIR; i++){
		sprintf(buf, "[%d] NextId = %3d  : %6.2f [sec]", i, AdditionalSound[i].get_Next_id(), AdditionalSound[i].get_timeLeft_to_next_kick());
		font.drawString(buf, ofs[i].x, ofs[i].y);
	}
}

/******************************
******************************/
void ofApp::keyPressed(int key){

}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
