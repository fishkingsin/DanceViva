//
//  Particle.h
//  Particles_with_circular_motion
//
//  Created by Kong king sin on 18/6/14.
//
//

#include "ofMain.h"
enum PARTICLE_MODE
{
    CIRCULAR,
    NOISE,
    RAIN,
};
class Particle {
public:
    
    void setup();
    void draw();
    void update();
    
    ofVec2f pos,vel,acc,oldpos;
    float angle;
    ofColor color;
    int age;
    void circularMotion();
    void noiseMotion();
    void rainMotion();
//    bool isCircularMotion;
    PARTICLE_MODE mode;
    void switchMode(PARTICLE_MODE _mode, float centerX, float centerY);
    ofVec2f newTarget;
    
    
};