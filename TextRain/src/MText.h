//
//  Header.h
//  allAddonsExample
//
//  Created by James Kong on 5/2/12.
//  Copyright (c) 2012 yU+Co [lab] Hong Kong. All rights reserved.
//

#ifndef allAddonsExample_Header_h
#define allAddonsExample_Header_h
#include"ofMain.h"
#include "ofxTrueTypeFontUC.h"
class MText : public ofPoint , public ofBaseDraws
{
public:
    MText()
    {
        rotation = 0;
        scale = 1;
        delay = 0;
        color = 0;
        old.set(0,0);
        
        bScale = bRotate = false;   
    }
    void setup(ofxTrueTypeFontUC *_font,int _index,float _alpha = 0)
    {
        color.r = 0;
        color.g = 0;
        color.b = 0;
        color.a = _alpha*255;
        index = _index;
        font = _font;
        
        tweenIn.setParameters(0,easingcubic,ofxTween::easeIn,0,_alpha,0,0);
        tweenOut.setParameters(0,easingcubic,ofxTween::easeIn,0,_alpha,0,0);
        delay = 1000;
        tween2.setParameters(0,easingcubic,ofxTween::easeIn,0,y,0,0);
        tween3.setParameters(0,easingcubic,ofxTween::easeIn,0,x,0,0);
        
    }
    void setRotate(bool _bRotate = false  )
    {
        bRotate = _bRotate;
    }
    void setScale(bool _bScale = false  )
    {
        bScale = _bScale;
    }
    
    void update()
    {
        y = tween2.update();
        x = tween3.update();
        if(tweenOut.isDelaying())color.a = tweenIn.update()*255;   
        else color.a = tweenOut.update()*255;   
    }
    bool lightUp(wchar_t _i)
    {
        if(m_string[0]==_i)
        {
            tweenIn.setParameters(1,easingcubic,ofxTween::easeOut,0,1,1000,0);
            tweenOut.setParameters(3,easingcubic,ofxTween::easeOut,1,0,10000,1000);
            return true;
        }
        return false;
    }
    bool checkHit(string target)
    {
        color.r = 255;
        color.g = 255;
        color.b = 255;
        
        tweenIn.setParameters(1,easingcubic,ofxTween::easeOut,0,1,100,0);
        if(m_string.find(target)!=string::npos)
        {
            tweenOut.setParameters(2,easingcubic,ofxTween::easeOut,1,0,500,100);
            return false;
        }
        else
        {
            tweenOut.setParameters(3,easingcubic,ofxTween::easeOut,1,0,10000,100);
            return true;
        }
    }
//    bool checkHit(int _i)
//    {
//        color.r = 255;
//        color.g = 255;
//        color.b = 255;
//        tweenIn.setParameters(1,easingcubic,ofxTween::easeOut,0,1,100,0);
//        if(index!=_i)
//        {
//            tweenOut.setParameters(2,easingcubic,ofxTween::easeOut,1,0,500,100);
//            return false;
//        }
//        else
//        {
//            tweenOut.setParameters(3,easingcubic,ofxTween::easeOut,1,0,10000,100);
//            return true;
//        }
//    }
    bool checkHit()
    {
        color.r = 255;
        color.g = 255;
        color.b = 255;
        
        tweenIn.setParameters(3,easingcubic,ofxTween::easeIn,0,1,100,0);
        tweenOut.setParameters(2,easingcubic,ofxTween::easeOut,1,0,10000,100);
    }
    void fire()
    {
        tween2.setParameters(3,easingcubic,ofxTween::easeIn,y,old.y,10000-abs(old.y-y),0);
        tween3.setParameters(3,easingcubic,ofxTween::easeIn,x,old.x,10000-abs(old.x-x),0);  
    }
    void draw()
    {
        draw(ofPoint::x,ofPoint::y);
    }
    void draw(float _x,float _y){
        if(color.a>0)
        {
            ofEnableAlphaBlending();
            //        ofSetColor(255,0,0);
            //        ofNoFill();
            //        ofRect(x,y,font->getSize(),font->getSize());
            //        ofFill();
            ofPushMatrix();
            
            ofTranslate(_x,_y,this->z);
            if(bScale)ofScale(scale, scale);
            if(bRotate)ofRotate(rotation, 0, 0, 1);
            (bScale)?ofTranslate(-(font->getSize()*scale)/2,(font->getSize()*scale)/2):ofTranslate(-(font->getSize())/2,(font->getSize())/2);
            ofPushStyle();
//#define IS_DEBUG
#ifdef IS_DEBUG
                        ofSetColor(255,255,255);
#else
                        ofSetColor(color);
#endif

            
            font->drawString(m_string,0,0);
            ofPopStyle();
            ofPopMatrix();
            ofDisableAlphaBlending();
        }
    };
	void draw(float _x,float _y,float w, float h){
        draw(_x,_y);
    };
	
	void draw(const ofPoint & point){
		draw( point.x, point.y);
	}
	
	void draw(const ofRectangle & rect){
		draw(rect.x, rect.y, rect.width, rect.height); 
	}
	
	float getHeight(){};
	float getWidth(){};
	
	void setAnchorPercent(float xPct, float yPct){};
    void setAnchorPoint(float x, float y){};
	void resetAnchor(){};
    
    
    int index;
    string m_string;
    ofxTween tweenIn;
    ofxTween tweenOut;
    ofxTween tween2;
    ofxTween tween3;
    ofxTrueTypeFontUC *font;
    ofxEasingCubic 	easingcubic;
    
    float rotation;
    float scale;
    int delay;
    ofColor color;
    ofPoint old;
    
    bool bScale;
    bool bRotate;
    
};


#endif
