#include "StFftDrawBar.h"
#include "ofApp.h"

string StFftDrawBar::getName(){
    return "StFftDrawBar";
}

void StFftDrawBar::setup(){
    gui = new ofxUICanvas();
    gui->init(212, 10, 200, 200);
    gui->addSpacer();
    gui->addLabel("FFT Draw Bar");
    gui->addSpacer();
    gui->addIntSlider("PLOT HEIGHT", 0, ofGetHeight(), 500);
    gui->addSpacer();
    gui->addButton("SAVE SETTINGS", false);
    gui->loadSettings("StFftDrawBar.xml");
    gui->autoSizeToFitWidgets();
    gui->setVisible(false);
    ofAddListener(gui->newGUIEvent,this,&StFftDrawBar::guiEvent);
    
    app = ((ofApp*)ofGetAppPtr());
}

void StFftDrawBar::update(){
    gui->setVisible(getSharedData().guiVisible);
}

void StFftDrawBar::draw() {
    ofxUIIntSlider *gplotsize = (ofxUIIntSlider *)gui->getWidget("PLOT HEIGHT"); int plotsize = gplotsize->getValue();
    
    ofPushMatrix();
    ofTranslate(20, ofGetHeight() / 2 + plotsize / 2);
    app->fft->soundMutex.lock();
    app->fft->drawBins = ((ofApp*)ofGetAppPtr())->fft->middleBins;
    app->fft->soundMutex.unlock();
    ofScale((ofGetWidth() - 40) / float(app->fft->drawBins.size()) , 1.0);
    plot(app->fft->drawBins, -plotsize, plotsize / 2);
    ofPopMatrix();
}

void StFftDrawBar::plot(vector<float>& buffer, float scale, float offset) {
    ofNoFill();
    int n = buffer.size();
    ofPushMatrix();
    ofTranslate(0, scale / 2 + offset, 0);
    ofFill();

    for (int i = 0; i < n; i++) {
        int br = ofMap(buffer[i], 0, 1.0, 0, 255);
        ofSetColor(br);
        ofRect(n / 2.0 + i / 2.0, 0, 1, scale);
        ofRect(n / 2.0 - i / 2.0, 0, 1, scale);
    }
    glPopMatrix();
}

void StFftDrawBar::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    if(name == "SAVE SETTINGS"){
        gui->saveSettings("StFftDrawBar.xml");
    }
}

void StFftDrawBar::stateExit(){
    gui->setVisible(false);
}