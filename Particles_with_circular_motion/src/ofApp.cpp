#include "ofApp.h"
bool isDraw = false;
int ALPHA = 50;
//--------------------------------------------------------------
void ofApp::setup(){
    player.loadMovie("Finale-silhouette.mov");
    player.setLoopState(OF_LOOP_NONE);
    bAuto = false;
    ofSetBackgroundAuto(false);
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    ofBackground(0);
    fbo.allocate(1920,1080,GL_RGBA);
    server.setName("particle_silhouette");
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update();
//    ofSetWindowTitle(ofToString(ofGetFrameRate(),0));
    for (int i=0; i<particles.size(); i++) {
        particles[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    if(bAuto)
    {
        if(ALPHA<255)
        {
            ALPHA++;
        }
    }
    else
    {
        if(ALPHA>10)
        {
            ALPHA--;
        }
    }
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0,ALPHA);
    ofFill();
    ofRect(0, 0, fbo.getWidth(),fbo.getHeight());
    ofPopStyle();
    ofSetColor(255);
    
//    if (ofGetMousePressed()) {
//        img.draw(0,0);
//    }
    
    for (int i=0; i<particles.size(); i++) {
        Particle &p = particles[i];
        //p.color = img.getColor(p.pos.x,p.pos.y);
        p.draw();
    }
    if(!bAuto)
    {
    if(isDraw)
    {
        for (int i=0; i<100; i++) {
            createParticle();
        }
    }
    }
    fbo.end();
    ofSetColor(255);
    fbo.draw(0,0,1280,720);
    server.publishTexture(&fbo.getTextureReference());
    while (particles.size()>10000) {
        particles.erase(particles.begin());
    }

}
void ofApp::createParticle() {

    if(player.isFrameNew())
    {
        float x = ofRandom(0, fbo.getWidth());
        float y = ofRandom(0,fbo.getHeight());
        ofColor c = player.getPixelsRef().getColor(x,y);
        
        while(c == ofColor::white)
        {
            c = player.getPixelsRef().getColor(x,y);
        }
        Particle p;
        p.setup();
        p.pos.set(x,y);
        p.color = player.getPixelsRef().getColor(p.pos.x,p.pos.y);
        particles.push_back(p);
    }

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='s') ofSaveFrame();
    if (key=='q') ofEnableSmoothing();
    if (key=='Q') ofDisableSmoothing();
    if(key == '1')
    {
        bAuto = !bAuto;
//        ofSetBackgroundAuto(bAuto);
        for (int i=0; i<particles.size(); i++) {
            Particle &p = particles[i];
            p.toggleCircularMotion(fbo.getWidth()*(mouseX*1.0f/ofGetWidth()),fbo.getHeight()*(mouseY*1.0f/ofGetHeight()));
        }
    }
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
    isDraw = !isDraw;
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
