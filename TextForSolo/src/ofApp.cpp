#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    //this connects our app to any running openTSPS copy that is sending OSC messages to port 12000 with our IP
	receiver = new ofxTSPSReceiver();
	receiver->setListener( this );
	receiver->connect(PORT);
    
    individualTextureSyphonServer.setName("Texture Output");
    tex.allocate(200, 100, GL_RGBA);
    
    ofBuffer buf = ofBufferFromFile("text/HOW TO BE ALONE by Tanya Davis.txt");
//    ofLogVerbose() << buf;
    string text = buf.getText();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(100,100,100    );
	ofSetLineWidth(3);
	
	for(int i = 0; i < receiver->totalPeople(); i++){
		ofxTSPSPerson* person = receiver->personAtIndex(i);
		ofColor* color = (ofColor*)person->customAttributes;
		ofSetColor(color->r, color->g, color->b);
		for(int c = 1; c < person->contour.size(); c++){
			ofLine(person->contour[c-1].x*ofGetWidth(), person->contour[c-1].y*ofGetHeight(),
				   person->contour[c  ].x*ofGetWidth(), person->contour[c  ].y*ofGetHeight());
		}
	}
    
    individualTextureSyphonServer.publishTexture(&tex);
}
//called when the person enters the system
void ofApp::personEntered( ofxTSPSPerson* person, ofxTSPSScene* scene )
{
	ofColor* color = new ofColor();
	color->r = ofRandom(0, 255);
	color->g = ofRandom(0, 255);
	color->b = ofRandom(0, 255);
	color->a = 255;
	
	//put a color into the custom attributes field
	person->customAttributes = color;
	
}

//called each time the centroid moves (a lot)
void ofApp::personMoved( ofxTSPSPerson* person, ofxTSPSScene* scene )
{
}

//called one frame before the person is removed from the list to let you clean up
void ofApp::personWillLeave( ofxTSPSPerson* person, ofxTSPSScene* scene )
{
	//delete the color so we free up memory.
	delete (ofColor*)person->customAttributes;
}

//called every frame no matter what.
void ofApp::personUpdated(ofxTSPSPerson* person, ofxTSPSScene* scene)
{
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
