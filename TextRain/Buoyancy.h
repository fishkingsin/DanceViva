//
//  Buoyancy.h
//  allAddonsExample
//
//  Created by James Kong on 4/2/12.
//  Copyright (c) 2012 yU+Co [lab] Hong Kong. All rights reserved.
//

#ifndef allAddonsExample_Buoyancy_h
#define allAddonsExample_Buoyancy_h
//float __decay = 0.95f;
#include "ofMain.h"
#include "MText.h"
class FallingObject
{
public:
    FallingObject()
    {
        drawable = 0;
        scale = 0.5;
    }
	void setup(int _x,int _y , ofBaseDraws *_drawable, float _scale , ofColor _c)
	{
        c=_c;
        
		pos.set(_x,_y);
		a.set(0,ofRandom(0.05f,0.5f));
		v.set(0,ofRandom(0.1f,0.5f));
        drawable = _drawable;
        scale = _scale;
	}
	void update()
	{
		v+=a;
		v.y*=0.99;
		pos+=v;
        //scale-=(scale-1.0)/10;
	}
	void draw()
	{
        ofPushStyle();
        ofEnableAlphaBlending();
        
        ofPushMatrix();
        ofSetColor(c);
        ofTranslate(pos.x,pos.y);
        ofScale(scale,scale);
        if(drawable)drawable->draw(0,0);
		//ofCircle(pos.x,pos.y,5);
        ofPopMatrix();
        ofDisableAlphaBlending();
        ofPopStyle();
		
	}
    ofVec2f pos;
	ofVec2f v;
	ofVec2f a;
    float scale;
    ofColor c;
private:
	ofBaseDraws *drawable;
	
};
class Buoyancy{
	
public:


    //--------------------------------------------------------------
    void setup(){
        __decay = 0.95f;
        mode = 0;
        scale = 2;
        ofDirectory dir;
        rainTex.assign(dir.listDir("images/"),ofImage());
        for(int i = 0 ; i < rainTex.size(); i++)
        {
            rainTex[i].loadImage(dir.getPath(i));
        }
//        rainTex.loadImage("rain_tex.png");
        drawable = 0;
        isRain = false;
        float scale = 1;
        particleNum = (ofGetWidth()/scale)+2;
        lineStrip = new ofVec2f[particleNum];
        lineStrip1 = new float[particleNum-2];
        lineStrip2 = new float[particleNum-2];
        lineStrip3 = new float[particleNum-2];
//        stripColor = new ofFloatColor[particleNum];
        // ------------------------- wiggle worm 3d Vbo
        //stripDrawMode  =	;
        stripDrawMode  = GL_LINE_LOOP;
        
        int colorFlip = 0;
        int step = 0;
        for (int i=0; i<ofGetWidth(); i+=scale) {
            
//            stripColor[step].setHex(0x111111);
//            stripColor[step].normalize();
            lineStrip[step].set(ofRandom(10), ofRandom(10));
            
            lineStrip[step].x = i+1;	
            lineStrip[step].y = 0;	
            
            
            lineStrip1[step] = 0;	
            
            lineStrip2[step] = 0;	
            lineStrip3[step] = 0;
            step++;
            
        }
//        stripColor[particleNum-1].setHex(0x001100);
//        stripColor[particleNum-1].normalize();
//        stripColor[particleNum-2].setHex(0x000011);
//        stripColor[particleNum-2].normalize();
        lineStrip[particleNum-1].x =0;	
        lineStrip[particleNum-1].y = ofGetHeight()*1.5;	
        
        lineStrip[particleNum-2].x = ofGetWidth();	
        lineStrip[particleNum-2].y = ofGetHeight()*1.5;	
        
        
//        vbo.setVertexData(lineStrip, particleNum, GL_DYNAMIC_DRAW);
//        vbo.setColorData(stripColor, particleNum, GL_DYNAMIC_DRAW);
        
        randomIndex = new int[10];
        for(int i = 0  ; i < 10; i ++)
        {
            randomIndex[i] = ofRandom(particleNum-2);
        }
        waterHeight = ofGetHeight()+200;
        interval = 500;
        counter = 0;
    }
    
    //--------------------------------------------------------------
    void update(vector<MText*>mlist , int randRange){
        vector <FallingObject*>::iterator it;
        for(it =obj_list.begin() ; it!=obj_list.end() ; ++it)
        {
            FallingObject* p = *it;
            p->update();
            if(p->pos.y>waterHeight+50)
            {
                obj_list.erase(it);
                it--;
                
            }
        }
        
        for (int x=1; x<particleNum-2-1; x++){
            lineStrip3[x] = (lineStrip1[x-1] + lineStrip1[x+1]) *0.5;
            lineStrip3[x] = lineStrip3[x] * 2.0 - lineStrip2[x];
            lineStrip3[x] *= __decay;
            lineStrip[x].y -= (lineStrip[x].y-lineStrip3[x])*0.1;
            
        }
        
        
        
        
        
        for (int x=0; x<particleNum-2; x++){
            lineStrip2[x] -= (lineStrip2[x] - lineStrip1[x]) * __decay;
            lineStrip1[x] -= (lineStrip1[x] - lineStrip3[x]) * __decay;
        }
        for(int i = 0 ; i < obj_list.size() ; i++)
        {
            
            if(obj_list[i]->pos.y>=waterHeight && obj_list[i]->pos.y<=waterHeight+10)
            {
                
                if(mode!=0)waterHeight-=1;
                for (int _x=1; _x<particleNum-2; _x++){
                    float d =abs(obj_list[i]->pos.x-lineStrip[_x].x);
                    float area = 30;
                    if (d < area){
                        lineStrip1[_x] += pow(((area - d)/area),2) * 10.0f;
                    }
                }
            }
        }
        int timeDiff = ofGetElapsedTimeMillis()-counter;
        //interval = 10;
        if(isRain && timeDiff>interval)
		{
			int rand = ofRandom(1,randRange);
			for(int i = 0 ; i < rand ; i++)
			{
                addRain(ofRandom(ofGetWidth()),-100,mlist[ofRandom(mlist.size()-1)]);
				counter = ofGetElapsedTimeMillis();
			}
		}
        
        
    }
    
    //--------------------------------------------------------------
    void draw(vector<MText*>mlist){
        //	ofEnableLighting();
        ofPushMatrix();
        ofTranslate(0, waterHeight, 0);
        // the worm
//        glBegin(GL_LINE_STRIP);
//        glColor3f(0,0,0);
//        for(int i = 0 ; i < particleNum ; i++)
//        {
//            glVertex2f(lineStrip[i].x,lineStrip[i].y);
//            glVertex2f(lineStrip[i].x,ofGetHeight()*1.5);
//        }
//        
//        glEnd();
        glColor3f(0,0,0);
        ofBeginShape();
		
		for(int i = 0 ; i < particleNum ; i++)
		{
            if (i == 0){
				ofCurveVertex(lineStrip[0].x,lineStrip[0].y);
                ofCurveVertex( lineStrip[0].x,lineStrip[0].y);
			} else if (i == particleNum-1){
				ofCurveVertex(lineStrip[i].x,lineStrip[i].y);
                ofCurveVertex( lineStrip[0].x,lineStrip[0].y);
                ofCurveVertex( lineStrip[0].x,lineStrip[0].y);
			} else {
				ofCurveVertex(lineStrip[i].x,lineStrip[i].y);
			}
		}
		ofEndShape();
        ofSetColor(255);
        for(int i = 0  ; i < particleNum-2; i +=10)
        {
            MText *t  = mlist[i%mlist.size()];
            t->setRotate(true);
            t->setScale(true);
            //t->scale = 0.5;
//            float oR = t->scale;
//            t->scale = 0.5;
          //  t->rotation = ofVec2f(lineStrip[i].x,lineStrip[i].y).angle(ofVec2f(lineStrip[i+2].x,lineStrip[i+2].y));
            t->draw(lineStrip[i].x,lineStrip[i].y);
//            t->scale = oS;
            t->setScale(false);
            t->setRotate(false);
            //ofCircle(lineStrip[randomIndex[i]].x,lineStrip[randomIndex[i]].y,10);
        }
        ofPopMatrix();
        ofPushStyle();
        ofEnableAlphaBlending();
		
        
        for(int i = 0 ; i < obj_list.size() ; i++)
        {
            
            obj_list[i]->draw();
        }
        ofDisableAlphaBlending();
        ofPopStyle();
    }

    
    //--------------------------------------------------------------
    void toggleRain(){
            isRain = !isRain;
    }
    void toggleRainTex()
    {
        mode=(mode==0)?1:0;
    }
    
   
    
    //--------------------------------------------------------------
    void addRain(int x, int y , MText *drawable){

        FallingObject* b = new FallingObject();
        
        if(mode==0)b->setup(x,y,&rainTex[ofRandom(rainTex.size())],1,(mode==0)?ofColor(255):ofColor(0));
        else if(mode==1)
        {
            scale=0.5;//(scale-1.0)*0.0001;
            b->setup(x,y,drawable,scale,(mode==0)?ofColor(255):ofColor(0));
        }
        obj_list.push_back(b);

    }
    float scale;
//	ofVbo vbo;
	int stripDrawMode;
	int particleNum;
	ofVec2f				*lineStrip;
	float				*lineStrip1;
	float				*lineStrip2;
	float				*lineStrip3;
//	ofFloatColor		*stripColor;
	int *randomIndex;
	float waterHeight;
	vector<FallingObject*> obj_list;
    
	//cpounter
	float counter;
	float interval;
    
        bool isRain;
    MText *drawable;
    vector<ofImage> rainTex;
    int mode;
    float __decay;
    
};

#endif
