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
    isCircularMotion = true;
    
}

void Particle::draw() {
    ofSetColor(color,ofMap(age,0,100,255,50,true));
    ofLine(oldpos,pos);
    ofRect(pos,5,5);
}

void Particle::update() {
    if(isCircularMotion)
    {
        circularMotion();
    }
    else{
        noiseMotion();
    }
}
void Particle::toggleCircularMotion()
{
    isCircularMotion = !isCircularMotion;
    if(!isCircularMotion)
    {
        newTarget.x = ofRandom(pos.x-100,pos.x+100);
        newTarget.y = ofRandom(pos.y-100,pos.y+100);
        vel = (newTarget-pos)*0.05;
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
    vec *= 10 * ofGetLastFrameTime();
    oldpos = pos;
    pos += vel+vec;
    age++;
    
}