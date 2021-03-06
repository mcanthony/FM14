#include "StFftPixelate.h"

string StFftPixelate::getName(){
    return "StFftPixelate";
}

void StFftPixelate::setup(){
    gui = new ofxUICanvas();
    gui->init(212, 10, 200, 200);
    gui->addSpacer();
    gui->addLabel("SIMPLE PIXELATE");
    gui->addSpacer();
    gui->addSlider("RADIUS", 20, 200, 60);
    gui->addSlider("CIRCLE SCALE", 0, 2.0, 1.0);
    gui->addSlider("INTERPORATE", 0.0, 1.0, 0.1);
    gui->addIntSlider("FADE", 0, 127, 12);
    gui->addSlider("HUE", 0, 2.0, 1.0);
    gui->addSlider("SAT", 0, 2.0, 1.0);
    gui->addSlider("BR", 0, 2.0, 1.0);
    gui->addSpacer();
    gui->addButton("SAVE SETTINGS", false);
    gui->loadSettings("StFftPixelate.xml");
    gui->autoSizeToFitWidgets();
    gui->setVisible(false);
    ofAddListener(gui->newGUIEvent,this,&StFftPixelate::guiEvent);
    
    app = ((ofApp*)ofGetAppPtr());
    
    currentRotate = 45;
    currentSize = 1.0;
}

void StFftPixelate::update(){
    
}

void StFftPixelate::draw(){
    int camWidth = 1920;
    int camHeight = 1080;
    
    ofPixelsRef pixels = ((ofApp*)ofGetAppPtr())->blackmagic->colorPixels;
    pixels.resize(camWidth, camHeight);
    
    ofxUISlider *gradius = (ofxUISlider *)gui->getWidget("RADIUS"); float radius = gradius->getValue();
    ofxUISlider *gcircleScale = (ofxUISlider *)gui->getWidget("CIRCLE SCALE"); float circleScale = gcircleScale->getValue();
    ofxUISlider *ginterp = (ofxUISlider *)gui->getWidget("INTERPORATE"); float interp = ginterp->getValue();
    ofxUIIntSlider *gfade = (ofxUIIntSlider *)gui->getWidget("FADE"); int fade = gfade->getValue();
    ofxUISlider *ghue = (ofxUISlider *)gui->getWidget("HUE"); float hue = ghue->getValue();
    ofxUISlider *gsat = (ofxUISlider *)gui->getWidget("SAT"); float sat = gsat->getValue();
    ofxUISlider *gbr = (ofxUISlider *)gui->getWidget("BR"); float br = gbr->getValue();
    
    app->drawFbo->fbo.begin();
    app->drawFbo->blendMode = 0;
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(0, 0, 0, fade);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofTranslate(0, -app->drawFbo->top);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(32);
    
    float fftSum = 0;
    for (int i = 0; i < app->fft->drawBins.size(); i++) {
        fftSum += app->fft->drawBins[i];
    }
    
    float sizeScale = ofMap(app->oscControl->controlVal[2], 0, 127, 0.5, 2.0);
    
    currentRotate += (fftSum * 4.0 - currentRotate) / 10.0;
    currentSize += (fftSum / 30.0 * sizeScale - currentSize) * interp;
    
    if (pixels.size()>0){
        for (int i = 0; i < camWidth; i+=radius){
            for (int j = 0; j < camHeight - radius/2.0; j+=radius){
                ofColor col = pixels.getColor(i + radius / 2.0, j + radius / 2.0);
                ofPushMatrix();
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofTranslate(i, j);
                ofRotateZ(45);
                
                float controlHue;
                controlHue = ofMap(app->oscControl->controlVal[3], 0, 127, 0, 1);
                col.setHsb(col.getHue() * controlHue, col.getSaturation() * sat, col.getBrightness() * br * (fade / 255.0));
                ofSetColor(col);
                ofRect(0, 0, radius* circleScale * currentSize, radius* circleScale * currentSize);
                ofSetRectMode(OF_RECTMODE_CORNER);
                ofPopMatrix();
            }
        }
    }
    ofDisableBlendMode();
    app->drawFbo->fbo.end();
    
    gui->setVisible(getSharedData().guiVisible);
}

void StFftPixelate::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    if(name == "SAVE SETTINGS"){
        gui->saveSettings("StFftPixelate.xml");
    }
}

void StFftPixelate::stateExit(){
    gui->setVisible(false);
}
