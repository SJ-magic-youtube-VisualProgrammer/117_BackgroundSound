/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "AdditionalSound.h"

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		WINDOW_WIDTH	= 420,
		WINDOW_HEIGHT	= 240,
	};
	enum{
		NUM_ADDITIONAL_DIR = 2,
	};
	
	/****************************************
	****************************************/
	ofTrueTypeFont font;
	ofSoundPlayer backSound;
	
	ADDITIONAL_SOUND AdditionalSound[NUM_ADDITIONAL_DIR];
	
	/****************************************
	****************************************/
	void setup_Gui();
	void load_and_start_backMusic();
	
public:
	/****************************************
	****************************************/
	ofApp();
	~ofApp();
	void exit();
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
