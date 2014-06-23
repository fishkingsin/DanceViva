//
//  Particle.cpp
//  TextRain
//
//  Created by Kong king sin on 19/6/14.
//
//

#include "Particle.h"

void Particle:: setup(ofxTrueTypeFontUC *_type , string _theCharacter) {

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
    float scale = ofMap(age, 0, 50, 0, 1);
    ofScale(scale, scale);
    if(type)type->drawString(theCharacter, 0, 0);
        ofPopStyle();
    ofPopMatrix();

}

void Particle::update() {
    float t = (ofGetElapsedTimef()) * 0.9;
	float div = 250.0;
	float cur = ofGetElapsedTimef();
    float noiseStrength = 0.7;
    
    ofVec3f vec(
                ofSignedNoise(t, pos.y/div,pos.z/div)*noiseStrength,
                ofSignedNoise(pos.x/div, t, pos.z/div)*noiseStrength,
                ofSignedNoise(pos.x/div, t, pos.y/div)*noiseStrength);
//    angle += ofSignedNoise(vel.x, vel.y)*TWO_PI;
    if(vel.x>10)
    {
        vec *= vel ;
    }
    else
    {
            
        vec *= 5;
    }
//    vel.rotate(angle,ofVec3f(0,0,1));
    oldpos = pos;
    vel*=damp;
    pos += vel+vec;
    if(age<80)age++;
}
