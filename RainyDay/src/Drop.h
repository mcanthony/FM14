#pragma once
#include "ofMain.h"
#include "ofxCv.h"

class Drop {
public:
    Drop(ofImage *image, ofImage *blur, ofVec2f position, float radius, int width, int height, float ratio);
    ~Drop();
    void update();
    void draw();
    void checkCollision();
    void kill();
    
    float radius;
    float imageRatio;
    
    ofImage *sourceImage;
    ofImage *maskImage;
    ofImage *blurImage;
    
    ofImage bgImage;
    ofImage dropImage;
    ofImage inputImage;

    ofVec2f position;
    ofVec2f velocity;
    
    int drawWidth;
    int drawHeight;
    
    bool moving;
};