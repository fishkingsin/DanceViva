#include "testApp.h"
#include "Mode2.h"
bool bDebug = false;
//--------------------------------------------------------------
void testApp::setup(){
    
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
    sense2_mode = 1 ;
    //gui

    //
    Mode2Setup();
    //mB2d.setup();
    buoyancy.setup();
    buoyancy.drawable = mText[ofRandom(mText.size()-1)];
    

    //mainOutputSyphonServer.setName("Simple Server");

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
    if(sense2_mode==0)
    {
        buoyancy.interval = gui.getValueI("BUOYANCY_INTERVAL");
        buoyancy.update(mText,mouseX);
    }
    else if(sense2_mode==1)
    {
        Mode2Update();
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.5,0.5,0.5, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(sense2_mode==0)
    {
        ofSetColor(255);
        image.draw(0,0,ofGetWidth(),ofGetHeight());
        buoyancy.draw(mText);
    }
    else if(sense2_mode==1)
    {

        Mode2Draw();
    }
    //if(ss.size()>selectedText)font.drawString(ss[selectedText], 20, ofGetHeight()-64);
    //mainOutputSyphonServer.publishScreen();
    //    gui.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    vector<MText*>::iterator it1;
    switch (key)
    {
            case '1':
            sense2_mode = 0;
            break;
        case '2':
            sense2_mode = 1;
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
                wstring target = ss[selectedText];
                for(int i = 0 ; i < target.length() ; i++)
                {
                    if(ptr->lightUp(target[i]))                            
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
            (sense2_mode==1)?sense2_mode=0:sense2_mode=1;
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
            buoyancy.toggleRain();
            
            break;
            case 'R':
            buoyancy.toggleRainTex();
            break;
            case 'f':
            ofToggleFullscreen();
            break;
    }
}
void testApp::nextText()
{
    selectedText++;
    selectedText%=ss.size();
}
void testApp::prevText()
{
    selectedText--;
    (selectedText<0)?selectedText=ss.size()-1:selectedText;
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(sense2_mode==0)
    {
        buoyancy.addRain(x, y, mText[ofRandom(mText.size()-1)]);
    }
    else if(sense2_mode==1)
    {
        nextText();
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

