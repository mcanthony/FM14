#include "OpVector.h"
#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void OpVector::stateEnter(){
    ofSetColor(0);
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
}

void OpVector::setup() {
    cvWidth = 80;
    cvHeight = 60;
    
    int camWidth = ((testApp*)ofGetAppPtr())->syphonIO.width;
    int camHeight = ((testApp*)ofGetAppPtr())->syphonIO.height;
    pixels.allocate(camWidth, camHeight, 3);
    
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

void OpVector::update() {
    farneback.setPyramidScale(pyrScale);
    farneback.setNumLevels(levels);
    farneback.setWindowSize(winsize);
    farneback.setNumIterations(iterations);
    farneback.setPolyN(polyN);
    farneback.setPolySigma(polySigma);
    farneback.setUseGaussian(OPTFLOW_FARNEBACK_GAUSSIAN);
    
    ((testApp*)ofGetAppPtr())->syphonIO.texture.readToPixels(pixels);
    pixels.resize(cvWidth, cvHeight);
    farneback.calcOpticalFlow(pixels);
    
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->resetForce();
        particles[i]->updateForce();
        particles[i]->updatePos();
    }
}

void OpVector::draw() {
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(0,15);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(8);
    int camWidth = ((testApp*)ofGetAppPtr())->syphonIO.width;
    int camHeight = ((testApp*)ofGetAppPtr())->syphonIO.height;
    
    if (farneback.getWidth() > 0) {
        ofVec2f scale = ofVec2f(ofGetWidth()/farneback.getWidth()/3, ofGetHeight()/farneback.getHeight());
        ofPushMatrix();
        ofTranslate(ofGetWidth()/3, 0);
        ofScale(scale.x, scale.y);
        
        int skip = 1;
        for (int i = 0; i < 1000; i++) {
            int x = ofRandom(farneback.getWidth()-skip);
            int y = ofRandom(farneback.getHeight()-skip);
            ofRectangle region = ofRectangle(x, y, skip, skip);
            ofVec2f average = farneback.getAverageFlowInRegion(region);
            if (abs(average.x) + abs(average.y) > 1) {
                Particle *p = new Particle();
                p->setup(ofVec3f(x, y, 0), ofVec3f(average.x / 2.0, average.y / 2.0, 0));
                p->radius = (abs(average.x) + abs(average.y)) * 0.1;
                particles.push_back(p);
                if (particles.size() > 10000) {
                    particles.pop_front();
                }
            }
            /*
             int n = ((y * camWidth + x) * 3) * camWidth / farneback.getWidth();
             unsigned char r = pixels[n];
             unsigned char g = pixels[n + 1];
             unsigned char b = pixels[n + 2];
             ofSetColor(r, g, b);
             */
        }
        
        for (int i = 0; i < particles.size(); i++) {
            particles[i]->draw();
        }
        ofPopMatrix();
    }
    ofDisableBlendMode();
    
    ((testApp*)ofGetAppPtr())->syphonIO.server.publishScreen();
}

string OpVector::getName(){
    return "opvector";
}
