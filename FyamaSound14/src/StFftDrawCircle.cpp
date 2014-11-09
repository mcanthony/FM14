#include "StFftDrawCircle.h"
#include "ofApp.h"

string StFftDrawCircle::getName(){
    return "StFftDrawCircle";
}

void StFftDrawCircle::setup(){
    gui = new ofxUICanvas();
    gui->init(212, 10, 200, 200);
    gui->addSpacer();
    gui->addLabel("FFT Draw Bar");
    gui->addSpacer();
    gui->addSlider("CIRCLE SIZE", 0, ofGetHeight(), 50.0);
    gui->addIntSlider("SATURATION", 0, 255, 100);
    gui->addIntSlider("BRIGHTNESS", 0, 255, 100);
    gui->addSpacer();
    gui->addButton("SAVE SETTINGS", false);
    gui->loadSettings("StFftDrawCircle.xml");
    gui->autoSizeToFitWidgets();
    gui->setVisible(false);
    ofAddListener(gui->newGUIEvent,this,&StFftDrawCircle::guiEvent);
    
    app = ((ofApp*)ofGetAppPtr());
}

void StFftDrawCircle::update(){
    gui->setVisible(getSharedData().guiVisible);
}

void StFftDrawCircle::draw() {
    ofSetColor(255, 63);
    ofSetCircleResolution(64);
    ofxUISlider *gcirclesize = (ofxUISlider *)gui->getWidget("CIRCLE SIZE"); float circlesize = gcirclesize->getValue();
    ofxUIIntSlider *gsaturation = (ofxUIIntSlider *)gui->getWidget("SATURATION"); int saturation = gsaturation->getValue();
    ofxUIIntSlider *gbrightness = (ofxUIIntSlider *)gui->getWidget("BRIGHTNESS"); int brightness = gbrightness->getValue();
    app->fft->soundMutex.lock();
    app->fft->drawBins = ((ofApp*)ofGetAppPtr())->fft->middleBins;
    app->fft->soundMutex.unlock();

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (int i = 0; i < app->fft->drawBins.size(); i++) {
        float size = ofMap(app->fft->drawBins[i], 0, 1.0, 0, circlesize);
        float x = ofMap(i, 0, app->fft->drawBins.size(), 0, ofGetWidth()/2.0);
        float hue = ofMap(i, 0, app->fft->drawBins.size(), 0, 255);
        ofColor col;
        col.setHsb(hue, saturation, brightness);
        ofSetColor(col);
        ofCircle(ofGetWidth() / 2.0 + x, ofGetHeight() / 2.0, size);
        ofCircle(ofGetWidth() / 2.0 - x, ofGetHeight() / 2.0, size);
    }
    ofDisableAlphaBlending();
}

void StFftDrawCircle::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    if(name == "SAVE SETTINGS"){
        gui->saveSettings("StFftDrawCircle.xml");
    }
}

void StFftDrawCircle::stateExit(){
    gui->setVisible(false);
}