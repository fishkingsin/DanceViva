#include "testApp.h"
#include "Mode2.h"
bool bDebug = false;
float emmitX  = 0;
float emmitY  = 0;
bool bEmmit = false;
float noisePower = 0.4;
float noiseStrength = 0.6;

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(25);
    ofSetLogLevel(OF_LOG_VERBOSE);
    image.loadImage("DrawTest.png");
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofBackground(100,100,100);
    
    
    //gui
    ofxControlPanel::setBackgroundColor(simpleColor(30, 30, 60, 200));
    ofxControlPanel::setTextColor(simpleColor(240, 50, 50, 255));
    
    gui.loadFont("MONACO.TTF", 8);
    gui.setup("AM2", 0, 0,ofGetWidth()*(2.0f/3.0f), ofGetHeight());
    
    gui.addPanel("General",3, false);
    
    ofxControlPanel::setBackgroundColor(simpleColor(60, 30, 30, 200));
    gui.addPanel("Monitor1", 2, false);
    
    ofxControlPanel::setBackgroundColor(simpleColor(70, 70, 30, 200));
    gui.addPanel("Monitor2",2, false);
    
    ofxControlPanel::setBackgroundColor(simpleColor(30, 30, 30, 200));
    
    //--------- PANEL 1
    gui.setWhichPanel(0);
    
    gui.setWhichColumn(0);
    //some dummy vars we will update to show the variable lister object
    elapsedTime		= ofGetElapsedTimef();
    appFrameCount	= ofGetFrameNum();
    appFrameRate	= ofGetFrameRate();
    
    
    gui.enableIgnoreLayoutFlag();
    
    int num = inputList.listDir("text/");
    
    gui.addFileLister("input", &inputList, 200, 100);
    
    gui.disableIgnoreLayoutFlag();
    vector <guiVariablePointer> vars;
    vars.push_back( guiVariablePointer("ellapsed time", &elapsedTime, GUI_VAR_FLOAT, 2) );
    vars.push_back( guiVariablePointer("ellapsed frames", &appFrameCount, GUI_VAR_INT) );
    vars.push_back( guiVariablePointer("app fps", &appFrameRate, GUI_VAR_FLOAT, 2) );
    vars.push_back( guiVariablePointer("mouse x", &mouseX, GUI_VAR_INT) );
    vars.push_back( guiVariablePointer("mouse y", &mouseY, GUI_VAR_INT) );
    
    gui.addVariableLister("app vars", vars);
    gui.setWhichPanel("General");
    gui.setWhichColumn(1);
    
    vector<string> play_mode;
    play_mode.push_back("Sense1");
    play_mode.push_back("Sense2");
    play_mode.push_back("Sense3");
    gui.addSlider("BUOYANCY_INTERVAL","BUOYANCY_INTERVAL",1000,0,5000,true);
    gui.addMultiToggle("play_mode", "play_mode", 0, play_mode);
    gui.addSlider("emmitX","emmitX",0,0,ofGetWidth() , false);
    gui.addSlider("emmitY","emmitY",0,0,ofGetHeight() , false);
    gui.addSlider("noisePower","noisePower",0,0,10 , false);
    gui.addSlider("noiseStrength","noiseStrength",0,0,10 , false);
    gui.setWhichColumn(2);
    
    //    vector <string> boxNames;
    //    boxNames.push_back("Profile1");
    //    boxNames.push_back("Profile2");
    //    boxNames.push_back("Profile3");
    //    boxNames.push_back("Profile4");
    //    boxNames.push_back("Profile5");
    //    boxNames.push_back("Profile6");
    //    boxNames.push_back("Profile7");
    //    boxNames.push_back("Profile8");
    //    boxNames.push_back("Profile9");
    //    boxNames.push_back("Profile10");
    //    textDropDown = gui.addTextDropDown("profile", "CAMERA_PROFILE", currentSelected, boxNames);
    
    
    gui.setWhichPanel("Monitor2");
    gui.enableIgnoreLayoutFlag();
    gui.addLogger("events logger", &logger, 400, 200);
    gui.disableIgnoreLayoutFlag();
    
    gui.setDraw(false);
    gui.loadSettings("control_gui.xml");
    sense_mode = 1 ;
    //gui
    
    //
    Mode2Setup();
    
    
    ofFile file("text/t2.txt");
    ofBuffer buffer = file.readToBuffer();
    charIndex = 0;
    m_text = buffer.getText();
    
    //mB2d.setup();
    //    buoyancy.setup();
    //    buoyancy.drawable = mText[ofRandom(mText.size()-1)];
    
    
    //mainOutputSyphonServer.setName("Simple Server");
    syphon.setName("TextRain");
    
    duration.setup(12345);
	//ofxDuration is an OSC receiver, with special functions to listen for Duration specific messages
	//optionally set up a font for debugging
	duration.setupFont("MONACO.TTF", 12);
	ofAddListener(duration.events.trackUpdated, this, &testApp::trackUpdated);
}
//--------------------------------------------------------------
//Or wait to receive messages, sent only when the track changed
void testApp::trackUpdated(ofxDurationEventArgs& args){
	ofLogVerbose("Duration Event") << "track type " << args.track->type << " updated with name " << args.track->name << " and value " << args.track->value << endl;
    if(args.track->name=="/text")
    {
        if(sense_mode==1)
        {
            ofLogVerbose(args.track->name) << args.track->flag;
            targetString = args.track->flag;
            //        bang_mtext = new MText();
            //        bang_mtext->setup(&font,0,1);
            //        bang_mtext->m_string = targetString;
            //        bang_mtext->old.set(ofGetWidth()*0.5,ofGetHeight()*0.5);
            //        bang_mtext->ofPoint::set(ofGetWidth()*0.5,ofGetHeight()*0.5,0);
            //        bang_mtext->x = ofGetWidth()*0.5;
            //        bang_mtext->y = ofGetHeight()*0.5;
            //        bang_mtext->scale = 1;
            //        bang_mtext->rotation = 0;
            //        mText.push_back(bang_mtext);
            createRipple(targetString, ofRandom(0,ofGetWidth()), ofRandom(0, ofGetHeight()));
        }
    }
    if(args.track->name=="/command")
    {
        if( args.track->flag == "mode1")
        {
            keyPressed('1');
        }
        else if( args.track->flag == "mode2")
        {
            keyPressed('2');
        }
        else if( args.track->flag == "fadeout")
        {
            keyPressed('3');
        }
    }if(args.track->name=="/emmit")
    {
        bEmmit = args.track->on;
        //         addParticle(emmitX,emmitY,0,0);
        
    }
    if(args.track->name=="/noisePower")
    {
        noisePower = args.track->value;
    }
    if(args.track->name=="/noiseStrength")
    {
        noiseStrength = args.track->value;
    }
}

//this captures all our control panel events - unless its setup differently in testApp::setup
//--------------------------------------------------------------
void testApp::eventsIn(guiCallbackData & data)
{
    
    //lets send all events to our logger
    if ( !data.isElement( "events logger" ) )
    {
        string logStr = data.getXmlName();
        
        for (int k = 0; k < data.getNumValues(); k++)
        {
            logStr += " - " + data.getString(k);
        }
        
        logger.log(OF_LOG_NOTICE, "event - %s", logStr.c_str());
    }
    
    // print to terminal if you want to
    //this code prints out the name of the events coming in and all the variables passed
    printf("testApp::eventsIn - name is %s - \n", data.getXmlName().c_str());
    if ( data.getDisplayName() != "" )
    {
        printf(" element name is %s \n", data.getDisplayName().c_str());
    }
    for (int k = 0; k < data.getNumValues(); k++)
    {
        if ( data.getType(k) == CB_VALUE_FLOAT )
        {
            printf("%i float  value = %f \n", k, data.getFloat(k));
        }
        else if ( data.getType(k) == CB_VALUE_INT )
        {
            printf("%i int    value = %i \n", k, data.getInt(k));
        }
        else if ( data.getType(k) == CB_VALUE_STRING )
        {
            printf("%i string value = %s \n", k, data.getString(k).c_str());
        }
    }
    
    printf("\n");
}

//--------------------------------------------------------------
void testApp::update(){
    updateGUI();
    //    if(sense_mode==0)
    {
        if(bEmmit)
        {
            //            for(int i = 0 ; i < 10 ; i ++)
            {
                float hW = ofGetWidth()*0.5;
                float hH = ofGetHeight()*0.5;
                float vx = (((sinf(ofRandomf())*ofRandom(-hW,hW))+hW)-emmitX)*0.02;
                float vy = (((cosf(ofRandomf())*ofRandom(-hH,hH))+hH)-emmitY)*0.02;
                addParticle(emmitX,emmitY,vx,vy);
            }
        }
        //        buoyancy.interval = gui.getValueI("BUOYANCY_INTERVAL");
        //        buoyancy.update(mText,mouseX);
        
        vector<Particle*>::iterator it;
        float t = (ofGetElapsedTimef()) * noisePower;
        float div = 250.0;
        float cur = ofGetElapsedTimef();
        if(sense_mode == 2 )
        {
            if(charIndex>0)
            {
    //            float hW = ofGetWidth()*0.5;
    //            float hH = ofGetHeight()*0.5;
                float vx = (emmitX - particles[charIndex]->pos.x)*0.02;
                float vy = (emmitY - particles[charIndex]->pos.y)*0.02;
                particles[charIndex]->vel.set(vx,vy);
                charIndex--;
            }
        }
        for(it = particles.begin() ; it!=particles.end() ; ++it)
        {
            
            Particle * p = *it;
            
            ofVec3f vec(
                        ofSignedNoise(t, p->pos.y/div,p->pos.z/div)*noiseStrength,
                        ofSignedNoise(p->pos.x/div, t, p->pos.z/div)*noiseStrength,
                        ofSignedNoise(p->pos.x/div, t, p->pos.y/div)*noiseStrength);
            if(p->vel.x>10)
            {
                vec *= p->vel*10 ;
            }
            else
            {
                
                vec *= 5;
            }
            
            p->oldpos = p->pos;
            
            
            p->pos += p->vel+vec;
            if(sense_mode == 2 )
            {
                float dist = ofDist(p->pos.x,p->pos.y,emmitX,emmitY);
                p->age = (dist>80)?80:dist;
//                if(p->age>0)p->age--;
            }
            else
            {
                p->vel*=p->damp;
                if(p->age<80)p->age++;
            }
            
            
        }
    }
    if(sense_mode==1)
    {
        Mode2Update();
    }
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0,0,0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ofEnableAlphaBlending();
    if(sense_mode==1)
    {
        
        Mode2Draw();
    }
    //    if(sense_mode==0)
    {
        
        vector<Particle*>::iterator it;
        for(it = particles.begin() ; it!=particles.end() ; ++it)
        {
            Particle * p = *it;
            p->draw();
        }
        
        //        buoyancy.draw(mText);
    }
    //    else
    
    ofDisableAlphaBlending();
    //if(ss.size()>selectedText)font.drawString(ss[selectedText], 20, ofGetHeight()-64);
    //mainOutputSyphonServer.publishScreen();
    //    gui.draw();
    syphon.publishScreen();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    vector<MText*>::iterator it1;
    switch (key)
    {
        case '1':
            charIndex = 0;
            sense_mode = 0;
            clearParticle();
            break;
        case '2':
            //            clearParticle();
            sense_mode = 1;
            break;
        case '3' :
            sense_mode = 2;
            charIndex = this->particles.size()-1;
            break;
            
        case ']':
            gui.setWhichPanel(gui.getWhichPanel()+1);
            break;
        case '[':
            gui.setWhichPanel(gui.getWhichPanel()-1);
            break;
        case OF_KEY_LEFT:
            nextText();
            break;
        case OF_KEY_RIGHT:
            prevText();
            break;
        case OF_KEY_UP:
            nextText();
            for(it1=mText.begin(); it1!=mText.end();++it1)
            {
                
                MText * ptr = *it1;
                //                targetString = targetStrings[selectedText];
                for(int i = 0 ; i < targetString.length() ; i++)
                {
                    if(ptr->lightUp(targetString[i]))
                    {
                        break;
                    }
                }
            }
            
            break;
            
        case OF_KEY_RETURN:
            for(it1=mText.begin(); it1!=mText.end();++it1)
            {
                MText * ptr = *it1;
                ptr->fire();
            }
            
            break;
        case '\\':
            (sense_mode==1)?sense_mode=0:sense_mode=1;
            break;
        case ' ' :
            bDebug = !bDebug;
            if (bDebug)
            {
                ofShowCursor();
                gui.setDraw(true);
            }
            else
            {
                ofHideCursor();
                gui.setDraw(false);
            }
            break;
        case 'r':
            //            buoyancy.toggleRain();
        {
            //    vel.x = (((sinf(ofRandomf())*ofRandom(-500,500))+ofGetWidth()*0.5)-pos.x)*0.02;
            //    vel.y = (((cosf(ofRandomf())*ofRandom(-500,500))+ofGetHeight()*0.5)-pos.y)*0.02;
            
            for(int i = 0 ; i < 10 ; i ++)
            {
                float vx = (((sinf(ofRandomf())*ofRandom(-300,300))+ofGetWidth()*0.5)-mouseX)*0.02;
                float vy = (((cosf(ofRandomf())*ofRandom(-300,300))+ofGetHeight()*0.5)-mouseY)*0.02;
                addParticle(mouseX,mouseY,vx,vy);
            }
        }
            break;
        case 'R':
            //            buoyancy.toggleRainTex();
            break;
        case 'f':
            ofToggleFullscreen();
            break;
    }
}
void testApp::nextText()
{
    selectedText++;
    //    selectedText%=targetStrings.size();
}
void testApp::prevText()
{
    selectedText--;
    //    (selectedText<0)?selectedText=targetStrings.size()-1:selectedText;
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    //    for(int i =0 ; i < 10 ; i++)
    {
        addParticle(x,y,0,0);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(sense_mode==0)
    {
        //for(int i =0 ; i < 10 ; i++)
        //{
        //        addParticle(x,y);
        //}
        
        //        buoyancy.addRain(x, y, mText[ofRandom(mText.size()-1)]);
    }
    else if(sense_mode==1)
    {
        nextText();
        //        ofLogVerbose("targetString:") << targetStrings[selectedText];
        createRipple( targetString ,x,y);
    }
}

void testApp::createRipple(string target , int x ,int y)
{
    targetString = target;
    MData *_data = new MData();
    _data->deltaX = x;
    _data->deltaY = y;
    _data->isStarted = true;
    _data->deltaR = 0;
    mData.push_back(_data);
    bool bRotate = xml.getAttribute("TEXT","rotate",false,selectedText);
    bool bScale = xml.getAttribute("TEXT","scale",false,selectedText);
    vector<MText*>::iterator it1;
    for(it1=mText.begin(); it1!=mText.end();++it1)
    {
        MText * ptr = *it1;
        ptr->setScale(bScale);
        ptr->setRotate(bRotate);
    }
    radius = 7;
}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
void testApp::updateGUI(){
    emmitX  = gui.getValueF("emmitX");
    emmitY  = gui.getValueF("emmitY");
    //    noisePower = gui.getValueF("noisePower");
    //    noiseStrength = gui.getValueF("noiseStrength");
    //    int selected = gui.getValueI("CAMERA_PROFILE");
    //    if (selected!=currentSelected)
    //    {
    //        currentSelected = selected;
    //        gui.setValueB("TOGGLE_PROFILE",true);
    //        switch (currentSelected)
    //        {
    //            case 0:
    //                break;
    //            case 1:
    //                break;
    //            case 2:
    //                break;
    //            case 3:
    //                break;
    //            case 4:
    //                break;
    //            case 5:
    //                break;
    //            case 6:
    //                break;
    //            case 7:
    //                break;
    //            case 8:
    //                break;
    //            case 9:
    //                break;
    //            case 10:
    //                break;
    //        }
    //    }
    
    bool reload = inputList.selectedHasChanged();
    if (reload)
    {
        setupInput();
        inputList.clearChangedFlag();
    }
    elapsedTime		= ofGetElapsedTimef();
    appFrameCount	= ofGetFrameNum();
    appFrameRate	= ofGetFrameRate();
    
}
void testApp::setupInput()
{
    string name = inputList.getSelectedName();
    int index = inputList.selected;
    
    bool usingTextFile = name.find("txt") != string::npos;
    ofFile textFile(inputList.getSelectedPath());
    filebuf *buff =  textFile.getFileBuffer();
    
    
    //process text file
}
void testApp::setupInput(int index)
{
    if (index<0 || index>inputList.getNumEntries())
        return ;
}

void testApp::addParticle(float x , float y , float vx, float vy)
{
    if(charIndex < m_text.length())
    {
        Particle* particle = new Particle();
        string t = "";
        t += m_text[charIndex];
        particle->pos.set(x,y,0);
        particle->vel.set(vx,vy,0);
        particle->setup(&font, t);
        
        particles.push_back(particle);
        charIndex++;
    }
}
void testApp::clearParticle()
{
    while(!particles.empty())
    {
        Particle* p = particles.back();
        p->~Particle();
        particles.pop_back();
    }
}
