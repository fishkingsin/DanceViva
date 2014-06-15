//
//  Word.h
//  TextForSolo
//
//  Created by Kong king sin on 15/6/14.
//
//

#ifndef __TextForSolo__Word__
#define __TextForSolo__Word__

#include "ofMain.h"
#include "ofxAnimatableOfPoint.h"
class Word : public ofxAnimatableOfPoint
{
public:
    void setup(string _word , float x ,float y);
    void draw();
    
private:
    string word;
    ofTrueTypeFont tpye;
};
#endif /* defined(__TextForSolo__Word__) */
