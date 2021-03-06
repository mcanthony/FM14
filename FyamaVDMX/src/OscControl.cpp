#include "OscControl.h"
#include "ofApp.h"

void OscControl::setup(){
    receiver.setup(9000);
}

void OscControl::update(){
    while(receiver.hasWaitingMessages()){

		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		if(m.getAddress() == "/FromVDMX/state"){
            state = m.getArgAsInt32(0);
            switch (state) {
                case 0:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("blank");
                    break;
                case 1:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("sakura2");
                    break;
                case 2:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("opdistort");
                    break;
                case 3:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("opbluevector");
                    break;
                case 4:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("opredvector");
                    break;
                case 5:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("opvector");
                    break;
                case 6:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("opvbo");
                    break;
                case 7:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("opnotes");
                    break;
                case 8:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("opsparkle");
                    break;
                case 9:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("stopmotion");
                    break;
                case 10:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("rgbdelay");
                    break;
                case 11:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("rgbvector");
                    break;
                case 12:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("phaseshift");
                    break;
                case 13:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("colorbubble");
                    break;
                case 14:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("through");
                    break;
                case 15:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("simple");
                    break;
                case 16:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("nofill");
                    break;
                case 17:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("box");
                    break;
                case 18:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("fatfont");
                    break;
                case 19:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("opcircle");
                    break;
                case 20:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("opparticle");
                    break;
                case 21:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("bubble");
                    break;
                case 22:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("sakura");
                    break;
                case 23:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("tile");
                    break;
                case 24:
                    ((ofApp*)ofGetAppPtr())->stateMachine.changeState("movetile");
                    break;
            }
		}
        if(m.getAddress() == "/FromVDMX/tile"){
            int div = m.getArgAsInt32(0) + 1;
            ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().tileDiv = div;
        }
        if(m.getAddress() == "/FromVDMX/cropPosY"){
            ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().cropPosY = m.getArgAsFloat(0);
        }
        if (m.getAddress() == "/FromVDMX/threeHead") {
            ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().threeHead = m.getArgAsInt32(0);
            //((ofApp*)ofGetAppPtr())->stateMachine.changeState("blank");
        }
        if (m.getAddress() == "/FromVDMX/redblue") {
            if(((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().redBlue){
                ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().redBlue = false;
            } else {
                ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().redBlue = true;
            }
        }
        if(m.getAddress() == "/FromVDMX/particlenum"){
            ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().particleNum = m.getArgAsFloat(0);
        }
        if(m.getAddress() == "/FromVDMX/stop"){
            ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().stop = m.getArgAsInt32(0);
        }
        if(m.getAddress() == "/FromVDMX/changecolor"){
            ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().changeColor = true;
        }
        if(m.getAddress() == "/FromVDMX/distortstrength"){
            ((ofApp*)ofGetAppPtr())->stateMachine.getSharedData().distortStrength = m.getArgAsFloat(0);
        }
    }
}