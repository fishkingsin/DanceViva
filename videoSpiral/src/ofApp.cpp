#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    glEnable(GL_DEPTH_TEST);
    ofSetBackgroundAuto(false);
    player.loadMovie("video.mov");
    
    player.play();
    for(int i = 0 ; i < NUM_TEXTURE ; i++)
    {
        textures[i].allocate(player.getWidth(),player.getHeight(),GL_RGB);
        pixels[i].allocate(player.getWidth(),player.getHeight() , OF_IMAGE_COLOR);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update();
    
    for(int i = NUM_TEXTURE-1 ; i >=0  ; i--)
    {
        if((i+1)<NUM_TEXTURE)
        {
        pixels[i+1].setFromPixels(pixels[i].getPixels(), player.getWidth(),player.getHeight(), OF_IMAGE_COLOR);
        }
        textures[i].loadData(pixels[i].getPixels(), player.getWidth(),player.getHeight(),GL_RGB);
    }
    pixels[0].setFromPixels(player.getPixels(), player.getWidth(),player.getHeight(), OF_IMAGE_COLOR);
    textures[0].loadData(pixels[0].getPixels(), player.getWidth(),player.getHeight(),GL_RGB);
}
float FValueB = 0.4;
float FValueA = 0.3;
int cx = 0;
int cy = 0;

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    cam.begin();
    
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(255,255,255,100);
    ofPushMatrix();
//    ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
    
    for(int i = 0 ; i < NUM_TEXTURE ; i++)
    {
        float angle = FValueB * i;

//        float x = sinf(i/NUM_TEXTURE)*100;
//        float y = cosf(i/NUM_TEXTURE)*100;
        float x2 = cx + (FValueA + FValueB * angle) * cos(angle);
        float y2 = cy + (FValueA + FValueB * angle) * sin(angle);

        ofPushMatrix();
        ofTranslate(-player.getWidth()*0.5,-player.getHeight()*0.5);
        ofRotate(sinf(TWO_PI*(i*1.0f/NUM_TEXTURE))*360, 1, 1, 0);
        ofTranslate(x2, y2 ,-i);
        textures[i].draw(0,0,player.getWidth(),player.getHeight());
        ofPopMatrix();
    }
    ofPopMatrix();
    ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
