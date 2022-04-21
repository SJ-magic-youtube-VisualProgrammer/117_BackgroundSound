/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "stdio.h"

#include "ofMain.h"
#include "ofxGui.h"

/************************************************************
************************************************************/
#define ERROR_MSG(); printf("Error in %s:%d\n", __FILE__, __LINE__);
#define WARNING_MSG(); printf("Warning in %s:%d\n", __FILE__, __LINE__);

/************************************************************
************************************************************/
enum{
	FONT_S,
	FONT_M,
	FONT_L,
	
	NUM_FONTS,
};

enum{
	BUF_SIZE_S = 500,
	BUF_SIZE_M = 1000,
	BUF_SIZE_L = 6000,
	BUF_SIZE_LL = 100000,
	UDP_BUF_SIZE = 100000,
};


/************************************************************
************************************************************/

/**************************************************
Derivation
	class MyClass : private Noncopyable {
	private:
	public:
	};
**************************************************/
class Noncopyable{
protected:
	Noncopyable() {}
	~Noncopyable() {}

private:
	void operator =(const Noncopyable& src);
	Noncopyable(const Noncopyable& src);
};


/**************************************************
**************************************************/
class GUI_GLOBAL{
private:
	/****************************************
	****************************************/
	
public:
	/****************************************
	****************************************/
	void setup(string GuiName, string FileName = "gui.xml", float x = 10, float y = 10);
	
	ofxGuiGroup Group_BackSound;
		ofxFloatSlider BackSound_vol;
	
	/*
	ofxGuiGroup Group_Light;
		ofxVec4Slider col_WhenTest;
		ofxFloatSlider Led_dimmer;
		ofxFloatSlider volLight_Back_max;
		
	ofxGuiGroup Group_VolLight;
		ofxFloatSlider Smooth_dt;
		ofxFloatSlider fft_map_max;
		
	ofxGuiGroup Group_Shutter;
		ofxFloatSlider DmxShutter_open;
		ofxFloatSlider DmxShutter_close;
	*/

	ofxPanel gui;
	
	bool b_Disp = false;
};

/************************************************************
************************************************************/
double LPF(double LastVal, double CurrentVal, double Alpha_dt, double dt);
double LPF(double LastVal, double CurrentVal, double Alpha);

bool checkIf_ContentsExist(char* ret, char* buf);
void Align_StringOfData(string& s);

/************************************************************
************************************************************/
extern GUI_GLOBAL* Gui_Global;

extern FILE* fp_Log;

extern int GPIO_0;
extern int GPIO_1;


/************************************************************
************************************************************/

