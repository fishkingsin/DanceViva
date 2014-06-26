//
//  Mode2.h
//  allAddonsExample
//
//  Created by James Kong on 25/1/12.
//  Copyright (c) 2012 yU+Co [lab] Hong Kong. All rights reserved.
//

#ifndef allAddonsExample_Mode2_h
#define allAddonsExample_Mode2_h

#include "testApp.h"


void testApp::Mode2Setup()
{
    sense_mode = 0;
//    selectedText = targetStrings.size()-1;
/*    if(xml.loadFile("text.xml"))
    {
        if(xml.pushTag("XML"))
        {
        int numTag = xml.getNumTags("TEXT");
                ofLog(OF_LOG_VERBOSE,"numTag = %i",numTag);
        for(int i = 0 ; i < numTag ; i++)
        {
            string text = xml.getAttribute("TEXT","text","NaN",i);
//            wstring wstr;
//            utf8ToWStr(text.c_str(),wstr);
            targetStrings.push_back(text);
//            ofLogVerbose() << "wstr = "<< text;
        }
            
        }
//        ofLog(OF_LOG_VERBOSE,"ss.size = %i",ss.size());
        
    }
    else
    {
//        targetString.push_back(wstring(L"愛上一個從來沒有愛過自己人"));
//        targetString.push_back(wstring(L"痛苦"));
//        targetString.push_back(wstring(L"相冊"));//2.40
//        targetString.push_back(wstring(L"美好回憶"));
//        targetString.push_back(wstring(L"失去你"));
//        targetString.push_back(wstring(L"對不起"));
//        targetString.push_back(wstring(L"對不起"));
//        targetString.push_back(wstring(L"我自己"));
//        targetString.push_back(wstring(L"空虛的房間圍繞"));
//        targetString.push_back(wstring(L"回憶"));
//        targetString.push_back(wstring(L"她身影"));
    }*/
    
    
    string str;// (L"人在情緒低時候就容易誤會容易看不到真實容易把別人對你好當成對你愛心裡其實很清楚愛上一個從來沒有愛過自己人其實是痛苦我要搬家了收拾東西時找到一本相冊才發現照片裡都裝著滿滿美好回憶一邊回憶過去一邊翻著每一頁記得每次和她說對不起後我眼淚就止不住其實失去你我最對不起是我自己回到只屬於自己新家後只有空虛的房間圍繞著我每當我和別人說起我過去點點滴滴才發現每個故事裡都有她身影人在情緒低時候就容易誤會容易看不到真實容易把別人對你好當成對你愛心裡其實很清楚其實是我要搬家了收拾東西時找到一本才發現照片裡都裝著滿滿一邊回憶過去一邊翻著每一頁記得每次和她說對不起後我眼淚就止不住其實我最是回到只屬於自己新家後只有著我每當我和別人說起我過去點點滴滴才發現每個故事裡都有人在情緒低時候就容易誤會容易看不到真實容易把別人對你好當成對你愛心裡其實很清楚其實是我要搬家了收拾東西時找到一本才發現照片裡都裝著滿滿一邊回憶過去一邊翻著每一頁記得每次和她說對不起後我眼淚就止不住其實我最是回到只屬於自己新家後只有著我每當我和別人說起我過去點點滴滴才發現每個故事裡都有人在情緒低時候就容易誤會容易看不到真實容易把別人對你好當成對你愛心裡其實很清楚其實是我要搬家了收拾東西時找到一本才發現照片裡都裝著滿滿一邊回憶過去一邊翻著每一頁記得每次和她說對不起後我眼淚就止不住其實我最是回到只屬於自己新家後只有著我每當我和別人說起我過去點點滴滴才發現每個故事裡都有人在情緒低時候就容易誤會容易看不到真實容易把別人對你好當成對你愛心裡其實很清楚其實是我要搬家了收拾東西時找到一本才發現照片裡都裝著滿滿一邊回憶過去一邊翻著每一頁記得每次和她說對不起後我眼淚就止不住其實我最是回到只屬於自己新家後只有著我每當我和別人說起我過去點點滴滴才發現每個故事裡都有");
    ofFile file("text/t2.txt");
    vector <string> words;
    if(file.is_open())
    {
        std::string delimiter = " ";
        ofBuffer buffer = file.readToBuffer();
        string line = buffer.getText();

        words = ofSplitString(line, delimiter);
        for (int i  = 0 ;  i < words.size(); i++) {
            ofLogVerbose("T2")<<words[i];
        }
        //want to erase first char
        //if txt is encode in BOM
//        if(line[0]==0xEF && line[1]==0xBB && line[2]== 0xBF)
//        {
//            memmove (line,line+3,strlen(line)-3);
//            
//        }
//        
//        utf8ToWStr(line,str);
        
    }
    
    int counter = 0;
    int fSize = 24;
    font.loadFont("Times New Roman.ttf",fSize,true,true);
    float lastX = 0;
    float lastY = fSize;
    for(int i = 0 ; i < words.size() ; i++)
    {
        string _word = words[counter%words.size()];
        int x = lastX+fSize;
        lastX = x+font.stringWidth(_word);
        if(lastX>ofGetWidth())
        {
            lastX = 0;
            lastY += fSize;
        }
        
        int y = lastY;
        lastY = y;
//        for (int i = -fSize; i < ofGetWidth()+fSize; i +=(fSize+5))
        {
            MText *newText = new MText();
            
            newText->old.x = x;//+ofRandomf()*fSize-(fSize/2);
            newText->old.y = y;//+ofRandomf()*fSize-(fSize/2);
            newText->x = newText->old.x;//i+ofRandomf()*fSize-(fSize/2);
            newText->y = newText->old.y;//j+ofRandomf()*fSize-(fSize/2);
//            newText->z = ofRandom(-200,00);
            
            newText->setup(&font,counter,0);
            counter++;
            newText->m_string = _word;//(L"1");

            int _index = counter;//Math.random()*ttext.length;
            //            newText->alpha = 1;
            //            newText->deltaY = i;
            //            newText->deltaX = j;
            //            newText->filters = filterArray;
            newText->rotation = (ofRandomf()*(2*PI)-PI);
            float s = ofRandomf() * 1.5 + 1;
            newText->scale = s;
            //            newText->isPlaying = false;
            mText.push_back(newText);
            //trace(newText);
            //            addChild(newText);
        }
        
        
    }
    glow.allocate(ofGetWidth(), ofGetHeight());
    glow.setPasses(3);
    glow.setRadius(7);
}
void testApp::Mode2Draw()
{    
    
    switch(sense_mode)
    {
        case 0:
//            ofClear(255,255,255, 255);
            drawText();
            
            break;
        case 1:
            glow.draw();
            
            break;
            
    }
    
}
void testApp::Mode2Update()
{
    vector<MText*>::iterator it1;
    vector<MData*>::iterator it2;
    current = ofGetElapsedTimeMillis();
    float timeDiff = current-pass;
    if(radius>0.1)radius-=(radius/timeDiff);
    for(it1=mText.begin(); it1!=mText.end();++it1)
    {
        MText * ptr = *it1;
        ptr->update();
    }
    if(sense_mode==1)
    {
        
//        int hitNum[5];
//        hitNum[0] = 1000;
//        hitNum[1] = 1001;
//        hitNum[2] = 1002;
//        hitNum[3] = 1003;
//        hitNum[4] = 1004;
        
        for(it2=mData.begin(); it2!=mData.end();++it2)
        {
            MData *_d = *it2;
            if(_d->isStarted)
            {
                _d->deltaR+=timeDiff/2;
                for(it1=mText.begin(); it1!=mText.end();++it1)
                {
                    MText * ptr = *it1;
                    if(ABS(_d->deltaR-ofDist(ptr->x,ptr->y,_d->deltaX,_d->deltaY))<20)
                    {
                        vector<string>subTargetString = ofSplitString(targetString," ");
                        for(int i = 0 ; i < subTargetString.size() ; i++)
                        {
//                            ofLogVerbose("subTargetString") << subTargetString[i];
                            if(ptr->checkHit(subTargetString[i]))
                            {
                                break;
                            }
                        }
                    }
                    
                }
                if (_d->deltaR>ofGetWidth()*2   )
                {
                    _d->isStarted = false;
                    _d->deltaR = 0;
                    
                    mData.erase(it2);
                    it2--;
                }
            }
        }
        pass = current; 
        
        
        glow.begin();
        glow.setRadius(radius);
        ofClear(0, 0, 0, 255);
        
        drawText();
        glow.end();
    }
    
}
void testApp::drawText()
{
    vector<MText*>::iterator it1;
    
    ofSetColor(255);
    for(it1=mText.begin(); it1!=mText.end();++it1)
    {
        MText * ptr = *it1;
        ptr->draw();
    }
}

#endif

