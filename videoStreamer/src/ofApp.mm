#include "ofApp.h"

#include "ofxPublishScreen.h"

ofColor color;

ofxPublishScreen::FboPublisher pub;

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	ofBackground(30);
	
	color.r = ofRandom(255);
	color.g = ofRandom(255);
	color.b = ofRandom(255);
	
	pub.setup(20000, 1136, 640);
    cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
    bonjourServer.startService( "_zmq._tcp.", "zmq", 20000 );
    player.loadMovie("videos/fingers.mov");
    player.play();
}

//--------------------------------------------------------------
void ofApp::update()
{
    player.update();
    // check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        ofLogVerbose("Address")<<m.getAddress();
        string msg_string;
        for(int i = 0; i < m.getNumArgs(); i++){
            
            msg_string += m.getArgTypeName(i);

            // display the argument - make sure we get the right type
            if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                msg_string += ofToString(m.getArgAsInt32(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                msg_string += ofToString(m.getArgAsFloat(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                msg_string += m.getArgAsString(i);
            }
            else{
                msg_string += "unknown";
            }
            ofLogVerbose("Arg "+ofToString(i))<<msg_string;
        }
    }
	pub.begin();

	ofClear(color.r, color.g, color.b);
    ofSetHexColor(0xFFFFFF);
    
    player.draw(20,20);
	ofCircle(ofGetMouseX(), ofGetMouseY(), 100);
	pub.end();
	
	ofSetWindowTitle(ofToString(pub.getFps(), 2));
}

//--------------------------------------------------------------
void ofApp::draw()
{
    
	pub.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	color.r = ofRandom(255);
	color.g = ofRandom(255);
	color.b = ofRandom(255);
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
