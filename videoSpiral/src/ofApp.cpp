#include "ofApp.h"
float FValueB = 0.4;
float FValueA = 0.3;
float FValueDepth = 10;
int cx = 0;
int cy = 0;
int rx = 0;
int ry = 0;
int rz = 0;
//--------------------------------------------------------------
void ofApp::setup(){
//    glEnable(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    ofSetBackgroundAuto(false);
    player.loadMovie("video.mov");
    
    player.play();
    for(int i = 0 ; i < NUM_TEXTURE ; i++)
    {
        textures[i].allocate(player.getWidth(),player.getHeight(),GL_RGB);
        pixels[i].allocate(player.getWidth(),player.getHeight() , OF_IMAGE_COLOR);
    }
    
    gui = new ofxUICanvas(0, 0, ofGetWidth()*0.5, ofGetHeight());
    
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = (ofGetWidth()*0.25)-xInit;
    int dim = 16;
    gui->addLabel("VdieoSpiral", OFX_UI_FONT_LARGE);
    gui->setDrawPaddingOutline(true);
//    gui->setDrawBack(true);
//    gui->setColorBack(ofColor(125,125,125,125));
    gui->addFPS();
    gui->addSlider("FValueA", 0.0, ofGetWidth(), FValueA, length-xInit, dim);
    gui->addSlider("FValueB", 0.00000f, 2.0f, FValueB, length-xInit, dim);
    gui->addSlider("FValueDepth", 0.00000f, 10, FValueDepth, length-xInit, dim);
    gui->addSlider("FValueRX", 0.00000f, 360, rx, length-xInit, dim);
    gui->addSlider("FValueRY", 0.00000f, 360, ry, length-xInit, dim);
    gui->addSlider("FValueRZ", 0.00000f, 360, rz, length-xInit, dim);
    
#ifdef USE_SYPHON
    mainOutputSyphonServer.setName("Screen Output");
#endif
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
    gui->loadSettings("GUI/guiSettings.xml");
	
	duration.setup(12345);
	ofAddListener(duration.events.trackUpdated, this, &ofApp::trackUpdated);
}
//--------------------------------------------------------------
//Or wait to receive messages, sent only when the track changed
void ofApp::trackUpdated(ofxDurationEventArgs& args){
	ofLogVerbose("Duration Event") << "track type " << args.track->type << " updated with name " << args.track->name << " and value " << args.track->value << endl;
		
	
}
void ofApp::exit()
{
    gui->saveSettings("GUI/guiSettings.xml");
    delete gui;
    
}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
    
    if(e.widget->getName()=="FValueA")
    {
        FValueA = ((ofxUISlider*)e.widget)->getScaledValue();
    }
    else if(e.widget->getName()=="FValueB")
    {
        FValueB = ((ofxUISlider*)e.widget)->getScaledValue();
    }
    else if(e.widget->getName()=="FValueDepth")
    {
        FValueDepth = ((ofxUISlider*)e.widget)->getScaledValue();
    }
    else if(e.widget->getName()=="FValueRX")
    {
        rx = ((ofxUISlider*)e.widget)->getScaledValue();
    }
    else if(e.widget->getName()=="FValueRY")
    {
        ry = ((ofxUISlider*)e.widget)->getScaledValue();
    }
    else if(e.widget->getName()=="FValueRZ")
    {
        rz = ((ofxUISlider*)e.widget)->getScaledValue();
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


//        ofRotate(sinf(x2)*NUM_TEXTURE, 1, 0, 0);
//        ofRotate(cosf(y2)*NUM_TEXTURE, 0, 1, 0);


        ofTranslate(x2, y2 ,FValueDepth*i);
        ofPushMatrix();
        ofTranslate(-player.getWidth()*0.5,-player.getHeight()*0.5 , -NUM_TEXTURE*FValueDepth);
        ofRotate(rx, 1, 0, 0);
        ofRotate(ry, 0, 1, 0);
        ofRotate(rz, 0, 0, 1);
        textures[i].draw(0,0,player.getWidth(),player.getHeight());
        ofPopMatrix();
        ofPopMatrix();
    }
    ofPopMatrix();
    ofPopStyle();
    cam.end();
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
