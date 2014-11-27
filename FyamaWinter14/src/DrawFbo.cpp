#include "DrawFbo.h"
#include "ofApp.h"

DrawFbo::DrawFbo(){
    top = 226;
    width = ofGetWidth();
    height = 630;
    
    fbo.allocate(width, height);
    fbo.begin();
    ofClear(0, 0, 0, 0);
    fbo.end();
    
    blendMode = 0;
}

void DrawFbo::draw(){
    if (blendMode == 0) {
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    } else {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    }

    fbo.draw(0, top);
}