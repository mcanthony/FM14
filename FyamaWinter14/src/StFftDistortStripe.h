#pragma once
#include "ofxState.h"
#include "SharedData.h"
#include "ofxUI.h"
#include "ofApp.h"

class StFftDistortStripe : public itg::ofxState<SharedData>{
public:
    string getName();
    void setup();
    void update();
    void draw();
    void stateExit();
    void createMesh();
    void guiEvent(ofxUIEventArgs &e);
    
    ofxUICanvas *gui;
    ofApp *app;
    ofEasyCam cam;
    
    ofMesh mesh;
    ofImage img;
    ofPixels pix;
    ofTexture tex;
    float stepSize, xSteps, ySteps;
    vector<ofVec3f> currentVertex;
};