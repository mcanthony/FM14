#include "OpRect.h"
#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void OpRect::stateEnter(){
    ofSetColor(0);
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
}

void OpRect::setup() {
    // GUI
    gui.setup();
    gui.add(pyrScale.setup("pyrScale", .5, 0, 1));
    gui.add(levels.setup("levels", 4, 1, 8));
    gui.add(winsize.setup("winsize", 8, 4, 64));
    gui.add(iterations.setup("iterations", 2, 1, 8));
    gui.add(polyN.setup("polyN", 7, 5, 10));
    gui.add(polySigma.setup("polySigma", 1.5, 1.1, 2));
    gui.add(OPTFLOW_FARNEBACK_GAUSSIAN.setup("OPTFLOW_FARNEBACK_GAUSSIAN", false));
}

void OpRect::update() {
    if (getSharedData().isFrameNew){
        farneback.setPyramidScale(pyrScale);
        farneback.setNumLevels(levels);
        farneback.setWindowSize(winsize);
        farneback.setNumIterations(iterations);
        farneback.setPolyN(polyN);
        farneback.setPolySigma(polySigma);
        farneback.setUseGaussian(OPTFLOW_FARNEBACK_GAUSSIAN);
        
        ofVideoGrabber cam = ((testApp*)ofGetAppPtr())->grabber.cam;
        farneback.calcOpticalFlow(cam);
        
        getSharedData().camTexture.readToPixels(pixels);
    }
}

void OpRect::draw() {
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(0, 15);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    int camWidth = getSharedData().camSize.x;
    int camHeight = getSharedData().camSize.y;
    
    if (farneback.getWidth() > 0) {
        ofVec2f scale = ofVec2f(ofGetWidth()/farneback.getWidth(), ofGetHeight()/farneback.getHeight());
        ofPushMatrix();
        ofScale(scale.x, scale.y);
        
        int skip = 4;
        for (int j = 0; j < farneback.getHeight(); j += skip) {
            for (int i = 0; i < farneback.getWidth(); i += skip) {
                ofRectangle region = ofRectangle(i, j, skip, skip);
                ofVec2f avrage = farneback.getAverageFlowInRegion(region) * 2.0;
                float radius = avrage.x + avrage.y;
                int n = ((j * camWidth + i) * 3) * camWidth / farneback.getWidth();
                unsigned char r = pixels[n];
                unsigned char g = pixels[n + 1];
                unsigned char b = pixels[n + 2];
                //ofSetColor(r, g, b);
                if (abs(radius) > skip / 2.0) {
                    radius = skip/2.0;
                }
                
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor(7,0,0);
                ofRect(i + skip/6.0, j, r * radius / 40.0, r * radius / 40.0);
                ofSetColor(0,7,0);
                ofRect(i + skip/6.0*3.0, j, g * radius / 40.0, g * radius / 40.0);
                ofSetColor(0,0,7);
                ofRect(i + skip/6.0*5.0, j, b * radius / 40.0 , b * radius / 40.0);
                //ofRect(i, j, radius*2.0, radius*2.0);
                
            }
        }
        ofPopMatrix();
    }
    
    ofDisableBlendMode();
    //gui.draw();
}

string OpRect::getName(){
    return "oprect";
}
