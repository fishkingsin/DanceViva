//
//  Word.cpp
//  TextForSolo
//
//  Created by Kong king sin on 15/6/14.
//
//

#include "Word.h"
void Word::setup(string _word , float x ,float y)
{
    word = _word;
    ofxAnimatableOfPoint::setPosition(ofPoint(x,y));
}

void Word::draw(){
    ofPushMatrix();
    ofPoint p = getCurrentPosition();
    ofTranslate(p.x, p.y, p.z);
    float s = 10.0f;
    ofRect( -s * 0.5f, -s * 0.5f, s, s );
	ofPopMatrix();
	
}