#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ofxSyphon.h"
//#include "ofxFX.h"
//#include "ofxGlow.h"
#include "ofxDuration.h"
class ofApp : public ofBaseApp{

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
    void createParticle();
    void createParticle(int minX , int minY , int maxX ,int maxY);
    void createParticle(ofRectangle rect);
    void createFadeoutParticle(int minX , int minY , int maxX ,int maxY);
    void createRain(int startX , int startY , int endX ,int endY);
    void createHeadParticle(int minX , int minY , int maxX ,int maxY);
    void toggleNoiseMode(float tx, float ty);
//    ofVideoPlayer player;
    ofImage image;
    
    vector<Particle> particles;
    vector<Particle>::iterator it;
    ofFbo fboImage;
    ofFbo fbo;
    bool bAutoBG;
    ofxSyphonServer server;
    
//    ofxGlow     glow;
    
    ofxDuration duration;
    
	void trackUpdated(ofxDurationEventArgs& args);
    ofPoint videoPos;
    ofRectangle rangeRect;
    float videoScale;

};
