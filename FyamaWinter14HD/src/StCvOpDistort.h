#pragma once
#include "ofxState.h"
#include "SharedData.h"
#include "ofxUI.h"
#include "ofxCv.h"
#include "Particle.h"
#include "ofApp.h"

class StCvOpDistort : public itg::ofxState<SharedData>{
public:
    string getName();
    void setup();
    void update();
    void draw();
    void createMesh();
    void guiEvent(ofxUIEventArgs &e);
    void stateExit();
    
    ofPixels pixels;
    ofTexture tex;
    ofxUICanvas *gui;
    
    ofxCv::FlowFarneback flow;
    
    int cvWidth, cvHeight;
    float pyrScale;
    int levels;
    int winsize;
    int iterations;
    int polyN;
    float polySigma;
    bool OPTFLOW_FARNEBACK_GAUSSIAN;
    
    ofMesh mesh;
    float stepSize, xSteps, ySteps;
    vector<ofVec2f> currentVertex;
    
    ofApp *app;
};