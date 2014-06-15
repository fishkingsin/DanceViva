#pragma once

#include "ofMain.h"
#include "ofxTSPSReceiver.h"
#include "ofxSyphon.h"
#define PORT 12000
#include "Word.h"
class ofApp : public ofBaseApp, public ofxTSPSListener{
    
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
	ofxTSPSReceiver* receiver;
	
	//called when the person enters the system
	void personEntered( ofxTSPSPerson* person, ofxTSPSScene* scene );
	//called each time the centroid moves (a lot)
	void personMoved( ofxTSPSPerson* person, ofxTSPSScene* scene );
	//called one frame before the person is removed from the list to let you clean up
	void personWillLeave( ofxTSPSPerson* person, ofxTSPSScene* scene );
	//called every frame no matter what.
	void personUpdated(ofxTSPSPerson* person, ofxTSPSScene* scene);
    
    ofTexture tex;
    
	ofxSyphonServer individualTextureSyphonServer;
};
