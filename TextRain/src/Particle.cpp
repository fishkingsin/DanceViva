//
//  Particle.cpp
//  TextRain
//
//  Created by Kong king sin on 19/6/14.
//
//

#include "Particle.h"

void Particle:: setup(ofxTrueTypeFontUC *_type , string _theCharacter) {
    vel.x = (((sinf(ofRandomf())*ofRandom(-500,500))+ofGetWidth()*0.5)-pos.x)*0.02;
    vel.y = (((cosf(ofRandomf())*ofRandom(-500,500))+ofGetHeight()*0.5)-pos.y)*0.02;
    angle = ofRandomf()*TWO_PI;
    age = 0;
    type = _type;
    theCharacter = _theCharacter;
    damp = 0.98;
}

void Particle::draw() {
    
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255,255,255,255*((100.0f-age)/100.0f));
    ofTranslate(pos.x,pos.y);

    if(type)type->drawString(theCharacter, 0, 0);
        ofPopStyle();
    ofPopMatrix();

}

void Particle::update() {
    float noisePower = 0.4;
    float noiseStrength = 0.6;
    float t = (ofGetElapsedTimef()) * noisePower;
	float div = 250.0;
	float cur = ofGetElapsedTimef();
    ofVec3f rot(
                ofSignedNoise(t,pos.y/div, pos.z/div)*noiseStrength,
                ofSignedNoise(pos.x/div, t, pos.z/div)*noiseStrength,
                0);//ofSignedNoise(billboards.getVertex(i).x/div, billboards.getVertex(i).y/div, t)*noiseStrength);
    
    rot *=   ofGetLastFrameTime();
    vel += rot;
    oldpos = pos;
    vel*=damp;
    pos += vel;
    if(age<20)age++;
}
