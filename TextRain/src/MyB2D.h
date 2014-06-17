//
//  MyB2D.h
//  allAddonsExample
//
//  Created by James Kong on 29/1/12.
//  Copyright (c) 2012 yU+Co [lab] Hong Kong. All rights reserved.
//

#ifndef allAddonsExample_MyB2D_h
#define allAddonsExample_MyB2D_h
#include "ofxBox2d.h"
#include "ofxTrueTypeFontUC.h"
class CustomParticle : public ofxBox2dCirTecle{
	
public:
	
	
	CustomParticle() {
	}
    ~CustomParticle() {
    }
	void setupFont(ofxTrueTypeFontUC *_font)
    {
        font = _font;
    }
	void draw() {
        if(font)
        {
        ofPushStyle();

		float radius = getRadius();
		
		glPushMatrix();
		glTranslatef(getPosition().x, getPosition().y, 0);
		
		ofSetColor(0,0,0);
		ofFill();
            wstring wstr(L"a");
		if(font)font->drawString(wstr,-radius/2, radius/2);	
        else ofCircle(0,0,radius);
		
		glPopMatrix();
        ofPopStyle();
        }
		
	}
    ofxTrueTypeFontUC *font;
};

class MyB2D
{
    public :
    MyB2D()
    {
        
    }
    void setup()
    {
        // Box2d
        b2d.init();
        b2d.setGravity(0, 20);
        b2d.createBounds(0, 0, ofGetWidth(), ofGetHeight());
        b2d.setFPS(60);
    }
    void draw()
    {

        // draw the box2d balls
        for(int i=0; i<customParticles.size(); i++) {
            customParticles[i].draw();
        }

    }
    
    void update()
    {
        b2d.update();	
    }
    void createBigBall(int x, int y)
    {

        CustomParticle p;
        
        // Mass Bounce Friction
        float r = ofRandom(32,64);		
        p.setPhysics(0.5, 0.001, 0);
        p.setup(b2d.getWorld(), x, y, r);

        customParticles.push_back(p);
        
    }
    ofxBox2d b2d;
    vector <CustomParticle>		customParticles;  //	this is a custom particle
    ofxTrueTypeFontUC *font;
    
};

#endif
