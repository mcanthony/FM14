#pragma once

#include "ofMain.h"
#include "ofxBlackMagic.h"

class BlackmagicCapture {
public:
    BlackmagicCapture(int width, int height, float framerate);
    void update();
    void draw();
    void exit();
    void changeInput(int mode);
    
    int width, height;
    float framerate;
    
    ofxBlackMagic blackmagic;
    ofVideoGrabber grabber;
    ofVideoPlayer video;
    ofTexture colorTexture;
    ofPixels colorPixels;
    ofFbo fbo;
    
    // bool useBlackmagic;
    
    // 0: BlackMagic, 1: internalCam, 2: Movie
    int inputMode;
    
};