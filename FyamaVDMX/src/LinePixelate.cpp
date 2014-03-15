#include "LinePixelate.h"
#include "testApp.h"

void LinePixelate::setup(){
    radius = 20;
    int width = ((testApp*)ofGetAppPtr())->syphonIO.width;
    int height = ((testApp*)ofGetAppPtr())->syphonIO.height;
    pixels.allocate(width, height, 3);
    
    camWidth = pixels.getWidth();
    camHeight = pixels.getHeight();
    //camWidth = 1920;
    //camHeight = 350;
    
    num = camWidth * camHeight / radius;
    for (int i = 0; i < num; i++) {
        float a = ofRandom(360);
        float l = ofRandom(10);
        angle.push_back(a);
        length.push_back(l);
    }
}

void LinePixelate::update(){
    pixels = ((testApp*)ofGetAppPtr())->syphonIO.croppedPixels;
}

void LinePixelate::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(0);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    ofVec2f scale;
    int camWidth = pixels.getWidth();
    int camHeight = pixels.getHeight();
    scale.x = ofGetWidth() / float(camWidth);
    scale.y = ofGetHeight() / float(camHeight);
    
    ofBackground(0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    if (pixels.size()>0){
        for (int i = 0; i < camWidth; i+=radius){
            for (int j = 0; j < camHeight; j+=radius){
                unsigned char r = pixels[(j * camWidth + i) * 3];
                unsigned char g = pixels[(j * camWidth + i) * 3 + 1];
                unsigned char b = pixels[(j * camWidth + i) * 3 + 2];
                
                ofPushMatrix();
                ofTranslate(i * scale.x, j * scale.y);
                
                int n = j * camWidth / radius + i / radius;
                
                float curAngle = angle[n] + ((r + g + b) * 2.0 - angle[n]) / 200.0;
                ofRotateZ(curAngle);
                angle[n] = curAngle;
                
                float curLength = length[n] + ((r + g + b) / 100.0 - length[n]) / 200.0;
                ofSetColor(r, g, b);
                ofRect(0, 0, curLength, curLength * 6.0);
                length[n] = curLength;
                ofPopMatrix();
            }
        }
    }
    ofDisableBlendMode();
    ((testApp*)ofGetAppPtr())->syphonIO.server.publishScreen();
}

string LinePixelate::getName(){
    return "line";
}