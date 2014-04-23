#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxState.h"
#include "SharedData.h"
#include "Particle.h"

class RgbDelayVector : public itg::ofxState<SharedData>{
    
public:
    void stateEnter();
    void stateExit();
    void setup();
    void update();
    void draw();
    string getName();
    
    ofxCv::FlowFarneback farneback;
    
    float pyrScale;
    int levels;
    int winsize;
    int iterations;
    int polyN;
    float polySigma;
    bool OPTFLOW_FARNEBACK_GAUSSIAN;
    
    ofxPanel gui;
    //ofxIntSlider sat;
    ofxFloatSlider skip;
    ofxFloatSlider thresh;
    //ofxIntSlider srcLevel;
    ofxIntSlider wireLevel;
    ofxFloatSlider radius;
    ofxFloatSlider accel;
    //ofxFloatSlider hue;
    //ofxFloatSlider sat;
    //ofxFloatSlider br;
    ofxFloatSlider minDist;
    ofxIntSlider num;
    ofxIntSlider max;
    ofxIntSlider bufLength;
    ofxIntSlider throughLevel;
    ofxIntSlider rgbLevel;
    
    ofPixels pixels;
    deque<Particle *> particles;
    int cvWidth, cvHeight;
    ofTexture tex;
    ofImage img;
    
    deque<ofTexture> texBuffer;
};