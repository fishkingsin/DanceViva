#include "ofApp.h"
bool isDraw = false;
int ALPHA = 50;
float imageScaleX = 0, imageScaleY = 0;
float emmitX = 0 , emmitY = 0;
bool isFaceout = false;
bool isRain = false;

int numDot = 0;
int numParticle = 1;
ofColor particle_color;
ofPixels pixel;
//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofSetLogLevel(OF_LOG_VERBOSE);
    image.loadImage("Finale-silhouette.png");
    
    fboImage.allocate(image.getWidth(),image.getHeight());
//    player.setLoopState(OF_LOOP_NONE);
//    player.play();
//    player.setPaused(true);
    bAutoBG = false;
    ofSetBackgroundAuto(false);
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    ofBackground(0);
    fbo.allocate(ofGetWidth(),ofGetHeight());
//    glow.allocate(ofGetWidth(), ofGetHeight());
//    glow.setPasses(3);
//    glow.setRadius(7);
    server.setName("particle_silhouette");
    duration.setup(12345);
	//ofxDuration is an OSC receiver, with special functions to listen for Duration specific messages
	//optionally set up a font for debugging
    duration.setupFont("GUI/NewMedia Fett.ttf", 12);
	ofAddListener(duration.events.trackUpdated, this, &ofApp::trackUpdated);
    videoScale = 1;
}
//--------------------------------------------------------------
//Or wait to receive messages, sent only when the track changed
void ofApp::trackUpdated(ofxDurationEventArgs& args){
//	ofLogVerbose("Duration Event") << "track type " << args.track->type << " updated with name " << args.track->name << " and value " << args.track->value << endl;
    if(args.track->name == "/video_x")
    {
        videoPos.x = args.track->value;
    }
    else if(args.track->name == "/video_y")
    {
        videoPos.y = args.track->value;
    }
    else if(args.track->name == "/video_scale")
    {
        videoScale = args.track->value;
    }
    else if(args.track->name == "/emmitX")
    {
        emmitX = args.track->value;
    }
    else if(args.track->name == "/emmitY")
    {
        emmitY = args.track->value;
    }
    else if(args.track->name == "/command")
    {
        if(args.track->flag=="start")
        {
            isDraw = !isDraw;
            
//            player.play();
        }
        else if(args.track->flag=="")
        {

            
        }
    }
    else if(args.track->name == "/fadeout")
    {
        isFaceout = args.track->on;
        if(isFaceout)toggleNoiseMode(emmitX,emmitY);
    }
    else if(args.track->name == "/rain")
    {
        bAutoBG = true;
        isRain = args.track->on;
//        if(isFaceout)toggleNoiseMode(emmitX,emmitY);
    }
    
    else if(args.track->name == "/particle_color")
    {
        particle_color = args.track->color;
        
    }
    else if(args.track->name == "/numParticle")
    {
        int value = args.track->value;
        numParticle = (value>1)?value:1;
        
    }
    else if(args.track->name == "/range_x")
    {
        int value = args.track->value;
        rangeRect.x = (value>1)?value:1;
        
    }
    else if(args.track->name == "/range_y")
    {
        int value = args.track->value;
        rangeRect.y = (value>1)?value:1;
        
    }
    else if(args.track->name == "/range_w")
    {
        int value = args.track->value;
        rangeRect.width = (value>1)?value:1;
        
    }
    else if(args.track->name == "/range_h")
    {
        int value = args.track->value;
        rangeRect.height = (value>1)?value:1;
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    imageScaleX = (image.getWidth()*videoScale);
    imageScaleY = (image.getHeight()*videoScale);
    fboImage.begin();
    ofClear(0,0,0,1);
    ofPushStyle();
    ofSetColor(255);

    {
//        if(ALPHA<10)
//        {
//            ALPHA++;
//        }
        if(isRain)
        {
            if(ALPHA<125)
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
    }
    
    {
        image.draw(videoPos.x, videoPos.y, imageScaleX, imageScaleY);
    }
    ofPopStyle();
    ofPopMatrix();
    fboImage.end();
    fboImage.readToPixels(pixel);
    if(isFaceout)
    {
        float targetY = emmitY-ofRandom(100,200);
        float targetX = emmitX+ofRandom(-100,100);
        for(int i = 0 ; i < 5 ; i++)
        {
            createFadeoutParticle(emmitX,emmitY,targetX,targetY);
        }
    }
    if(isRain)
    {

        float targetX = ofRandom(-10,10);
        int r = ofRandom(numParticle,numParticle+5);
        for(int i = 0 ; i < r ; i++)
        {
            createRain(ofRandom(0,ofGetWidth()),-100,targetX,ofGetHeight()-ofRandom(100,200));
        }

    }
    //    if(!bAutoBG)
    {
       
        if(isDraw && !isRain && !isFaceout )
        {
            for (int i=0; i<numParticle; i++) {
//                createParticle(videoPos.x,videoPos.y,videoPos.x+imageScaleX,videoPos.y+imageScaleY);
                createParticle(rangeRect);
            }
        }
        
    }
    
    
//    player.update();
//    ofSetWindowTitle(ofToString(ofGetFrameRate(),0));
    for(it = particles.begin() ; it!=particles.end() ; ++it) {
        Particle &p = *it;
        p.update();
        if(p.age>=100)
        {
            particles.erase(it);
            --it;
        }
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    // begin scene to post process
//    glow.begin();
    fbo.begin();
    
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0,ALPHA);
    ofFill();
    ofRect(0, 0, fbo.getWidth(),fbo.getHeight());
    ofPopStyle();

    {
        for(it = particles.begin() ; it!=particles.end() ; ++it) {
            Particle &p = *it;
            //p.color = img.getColor(p.pos.x,p.pos.y);
            p.draw();
        }
    }

    
    fbo.end();
    ofSetColor(255);
    fbo.draw(0,0,ofGetWidth(),ofGetHeight());
//    glow.end();
//    glow.draw();
    
    server.publishTexture(&fbo.getTextureReference());
    ofPushStyle();
    
    ofSetColor(255,255,255,50);
    fboImage.draw(0,0);
    ofPopStyle();

    
    ofPushStyle();
    ofNoFill();
    ofSetColor(255,0,0);
    ofRect(videoPos.x, videoPos.y, imageScaleX, imageScaleY);
    ofRect(emmitX,emmitY,10,10);
    ofPopStyle();

    ofPushStyle();
    ofNoFill();
    ofSetColor(0,255,0);
    ofRect(rangeRect);
    ofPopStyle();
    
    while (particles.size()>1000) {
        particles.erase(particles.begin());
    }
//    player.draw(0,0,100,100);

}
void ofApp::createParticle(ofRectangle rect) {
    createParticle(rect.x , rect.y , rect.x+rect.width  ,rect.y+rect.height);
}
void ofApp::createParticle(int minX , int minY , int maxX ,int maxY) {

//    if(player.isFrameNew())
    {
        float x = ofRandom(minX,maxX);
        float y = ofRandom(minY,maxY);


        ofColor c = pixel.getColor(x,y);
        
        if(c == ofColor::white)
        {
            Particle p;
            p.setup();
            p.pos.set(x,y);
            p.color = pixel.getColor(x,y);
            particles.push_back(p);
        }
    }

}
void ofApp::createHeadParticle(int minX , int minY , int maxX ,int maxY) {
    
    //    if(player.isFrameNew())
    {
        float x = ofRandom(minX,maxX);
        float y = ofRandom(minY,maxY);
        

        ofColor c = pixel.getColor(x,y);
        
        if(c != ofColor::black)
        {
            ofPushStyle();
            ofSetColor(pixel.getColor(x,y));
//            Particle p;
//            p.setup();
//            p.pos.set(x,y);
//            p.color = pixel.getColor(x,y);
//            particles.push_back(p);
            ofCircle(x, y, ofRandom(2,10));
            ofPopStyle();
        }
    }
    
}
void ofApp::createFadeoutParticle(int minX , int minY , int maxX ,int maxY) {
    
    //    if(player.isFrameNew())
//    {
//        float x = ofRandom(minX,maxX);
//        float y = ofRandom(minY,maxY);
//        ofPixels pixel;
//        fboImage.readToPixels(pixel);
//        ofColor c = pixel.getColor(x,y);
        
//        if(c == ofColor::white)
        {
            Particle p;
            p.setup();
            p.pos.set(minX,minY);
            p.color = particle_color;
            p.mode = NOISE;
            p.vel = -ofVec2f(p.pos.x+ofRandom(-200,200) - p.pos.x , p.pos.y+ofRandom(-200,200) - p.pos.y)*0.05;
            particles.push_back(p);
        }
//    }
    
}
void ofApp::createRain(int startX , int startY , int endX ,int endY) {
    
    //    if(player.isFrameNew())
    //    {
//    float x = ofRandom(minX,maxX);
//    float y = ofRandom(minY,maxY);
    //        ofPixels pixel;
    //        fboImage.readToPixels(pixel);
    //        ofColor c = pixel.getColor(x,y);
    
    //        if(c == ofColor::white)
    {
        Particle p;
        p.setup();
        p.pos.set(startX,startY);
        p.color = particle_color;
        p.mode = RAIN;
//        p.vel = ofVec2f(0,0);
        particles.push_back(p);
    }
    //    }
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='s') ofSaveFrame();
    if (key=='q') ofEnableSmoothing();
    if (key=='Q') ofDisableSmoothing();

    if(key == '1')
    {
        toggleNoiseMode(fbo.getWidth()*(emmitX*1.0f/ofGetWidth()),fbo.getHeight()*(emmitY*1.0f/ofGetHeight()));
    }
}
void ofApp::toggleNoiseMode(float tx, float ty)
{
    //bAutoBG = !bAutoBG;
    //        ofSetBackgroundAuto(bAutoBG);
    for(it = particles.begin() ; it!=particles.end() ; ++it) {
        Particle &p = *it;
        p.switchMode(NOISE,tx,ty);
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
//    player.play();
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
