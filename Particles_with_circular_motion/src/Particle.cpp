//
//  Particle.cpp
//  Particles_with_circular_motion
//
//  Created by Kong king sin on 18/6/14.
//
//

#include "Particle.h"

void Particle::setup() {
    vel.x = 2*ofRandomf();
    vel.y = 2*ofRandomf();
    angle = ofRandomf()*TWO_PI;
    age = 0;
    mode = CIRCULAR;
    
}

void Particle::draw() {
    ofPushStyle();
    if(mode == RAIN)

    {
        ofSetColor(color,ofMap(age,0,100,255,100,true));
    }
    else
    {
        
        ofSetColor(color,ofMap(age,0,100,255,0,true));
    }
    ofSetLineWidth(2);
    ofLine(oldpos,pos);
    ofRect(pos.x-1,pos.y-1,2,2);
    ofPopStyle();
}

void Particle::update() {
    if(mode == CIRCULAR)
    {
        circularMotion();
    }
    else if(mode == NOISE)
    {
        noiseMotion();
    }
    else if(mode == RAIN)
    {
        rainMotion();
    }
}
void Particle::switchMode(PARTICLE_MODE _mode, float centerX, float centerY)
{
    mode == _mode;
    if(mode == NOISE)
    {
        newTarget = ofVec2f(centerX - pos.x , centerY - pos.y);
        vel = (-newTarget)*0.05;
    }
    else if(mode == RAIN)
    {
        newTarget = ofVec2f(centerX - pos.x , centerY - pos.y);
        vel = (-newTarget)*0.05;
    }
}
void Particle::circularMotion()
{
    angle += ofSignedNoise(pos.x, pos.y)*TWO_PI;
    vel.rotate(angle);
    oldpos = pos;
    pos += vel;
    age++;

}
void Particle::noiseMotion()
{
    float t = (ofGetElapsedTimef()) * 0.9;
	float div = 250.0;
	float cur = ofGetElapsedTimef();
    float noiseStrength = 0.7;

    ofVec3f vec(
                ofSignedNoise(t, pos.y/div,pos.x/div)*noiseStrength,
                ofSignedNoise(pos.x/div, t, pos.y/div)*noiseStrength,
                0);
    vec *= 10 ;
    oldpos = pos;
    pos += vel+vec;
    age++;
    
}
void Particle::rainMotion()
{
//    float t = (ofGetElapsedTimef()) * 0.3;
//	float div = 250.0;
//	float cur = ofGetElapsedTimef();
//    float noiseStrength = 0.2;
//    
//    ofVec3f vec(
//                ofSignedNoise(t, pos.y/div,pos.x/div)*noiseStrength,
//                ofSignedNoise(pos.x/div, t, pos.y/div)*noiseStrength,
//                0);
//    vec *= 5 ;
    oldpos = pos;
    pos += vel;//+vec;
    age++;
    
}