#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxTween.h"
#include "ofxFX.h"
#include "ofxGlow.h"
//#include "ofxSyphon.h"
#include "ofxAutoControlPanel.h"
//#include "MyB2D.h"
#include "UTFHandler.h"
#include "Buoyancy.h"
#include "MText.h"
#include "ofxXmlSettings.h"
class MData
{
public:
    float deltaR;
    float deltaX;
    float deltaY;
    bool isStarted;
};
class testApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);	
	
    void nextText();
    void prevText();
    
    //mode2
    void Mode2Setup();
    void Mode2Update();
    void Mode2Draw();
    void drawText();
    
    //sense2
    int sense2_mode;
    vector<MText*>mText;
    vector<MData*>mData;
    ofxTrueTypeFontUC font;
    float current;
    float pass;
    //b2d
//    MyB2D mB2d;
    
    //filter 
    ofxGlow     glow;
    float radius;
    vector <wstring >ss;
    int selectedText;
    
    //syphon
    //ofxSyphonServer mainOutputSyphonServer;
    
    //gui
    float elapsedTime;
    int appFrameCount;
    float appFrameRate;
    ofxAutoControlPanel gui;
    simpleLogger logger;
    guiTypeTextInput *textinput;
    guiTypeTextDropDown *textDropDown;
    int currentSelected;
    void eventsIn(guiCallbackData & data);
    simpleFileLister inputList;
    void setupInput();
    void setupInput(int index);
    void updateGUI();
    
    
    //buoyancy
    Buoyancy buoyancy;
    ofImage image;
    //vector<ofImage> rainTexes;
    ofxXmlSettings xml;
};