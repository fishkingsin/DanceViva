#pragma once

#include "ofMain.h"
#define NUM_TEXTURE 100
#include "ofxUI.h"
#include "ofxDuration.h"
//#define USE_SYPHON
#ifdef USE_SYPHON
#include "ofxSyphon.h"
#endif
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void guiEvent(ofxUIEventArgs &e);
    ofVideoPlayer player;
    ofTexture textures[NUM_TEXTURE];
    ofEasyCam cam;
    ofPixels pixels[NUM_TEXTURE];
    
    
    ofxUICanvas *gui;
    
    
    ofxDuration duration;
    
	void trackUpdated(ofxDurationEventArgs& args);
	string ip;
	int port;
#ifdef USE_SYPHON
    ofxSyphonServer mainOutputSyphonServer;
#endif
};
