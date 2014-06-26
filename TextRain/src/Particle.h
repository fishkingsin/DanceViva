//
//  Particle.h
//  TextRain
//
//  Created by Kong king sin on 19/6/14.
//
//

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
class Particle {
public:
    
    void setup(ofxTrueTypeFontUC *type , string theCharacter);
    void draw();
//    void update();
    
    ofVec3f pos,vel,acc,oldpos;
    float angle;
    ofColor color;
    int age;
    float damp;
    ofxTrueTypeFontUC *type;
    string theCharacter;
};
