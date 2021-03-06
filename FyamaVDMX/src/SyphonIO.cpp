#include "SyphonIO.h"
#include "ofApp.h"

void SyphonIO::setup(int _width, int _height){
    width = _width;
    height = _height;
    
    //setup syphon client
    fboSyphonIn.allocate(width, height, GL_RGB);
    texture.allocate(width, height, GL_TEXTURE_2D);
    client.setup();
    
    //setup syphon server
    fboSyphonOut.allocate(SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA);
    server.setName("oF");
    
    outTex.allocate(SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA);
    fbo.allocate(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    //gui setup
    gui.setup();
    gui.add(fitScreen.setup("Fit to screen", false));
    gui.add(screenPos.setup("Screen position", ofGetWidth()/2, 0, ofGetWidth()));
    
    //initial crop Y position
    ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().cropPosY = 0.5;
}

void SyphonIO::update(){
    //update pixels
    texture.readToPixels(pixels);

    //crop pixels to cropPixels
    if (((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().threeHead == 0) {
        // threehead wide
        float y = ofMap(((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().cropPosY,
                        0, 1, 0, pixels.getHeight() - pixels.getHeight() / 3.0);
        pixels.cropTo(croppedPixels, 0, y, pixels.getWidth(), pixels.getHeight() / 3.0);
    } else if(((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().threeHead == 1) {
        // three screen tile
        ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().cropPosY = 0.5;
        pixels.resize(pixels.getWidth() / 3.0, pixels.getHeight() / 3.0);
        croppedPixels.allocate(pixels.getWidth() * 3, pixels.getHeight(), OF_PIXELS_RGB);
        pixels.pasteInto(croppedPixels, 0, 0);
        pixels.pasteInto(croppedPixels, pixels.getWidth(), 0);
        pixels.pasteInto(croppedPixels, pixels.getWidth() * 2, 0);
    } else if(((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().threeHead == 2) {
        // center screen only
        ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().cropPosY = 0.5;
        pixels.resize(pixels.getWidth() / 3.0, pixels.getHeight() / 3.0);
        croppedPixels.allocate(pixels.getWidth() * 3, pixels.getHeight(), OF_PIXELS_RGB);
        int i = 0;
        while( i < croppedPixels.size()) {
            croppedPixels[i] = 0;
            i++;
        }
        pixels.pasteInto(croppedPixels, pixels.getWidth(), 0);
    }
    
    //update syphone client
    ofSetColor(255);
    fboSyphonIn.begin();
    {
        ofClear(0,0,0,0);
        client.draw(0, 0, width, height);
    }
    fboSyphonIn.end();
    texture = fboSyphonIn.getTextureReference();
}

void SyphonIO::draw(){

}