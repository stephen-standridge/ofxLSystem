#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //light
    light.setPosition(500, 1000, 1600);
    light.enable();

    //camera
    cam.setPosition(0, -640, 300);
    cam.lookAt(ofVec3f(0, 0, 0));
    //cam.setNearClip(0.01f);
    cam.setMovementMaxSpeed( 25.f );

    //plane
    plane.setPosition(100, 50, 0);
    plane.set(20000, 20000);
    plane.setResolution(20, 20);

    roadMaterial.setDiffuseColor(ofFloatColor::moccasin);
    roadMaterial.setShininess(0.01);
    treeMaterial.setAmbientColor(ofFloatColor::hotPink);
    treeMaterial.setSpecularColor(ofFloatColor::blueSteel);
    treeMaterial.setShininess(0.04);
    for(unsigned int i =0; i<= 80; i++){
        ofxLSystem lystem;
        ofVec3f position = ofVec3f(ofRandom(-5000.f,5000.f), ofRandom(-5000.f,5000.f), 0);
        lsystem.setup("F", vector<string>{"F -> FF[+F][-F]"}, 4, 36.00);
        lsystem.setPosition(position);
        lsystem.build();
        treeContainer.push_back(lsystem);
    }
    ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDisableLighting();
    ofDisableDepthTest();
    ofBackgroundGradient( ofFloatColor::indigo, ofFloatColor::lemonChiffon, OF_GRADIENT_CIRCULAR);

    string msg = "\n\nfps: " + ofToString(ofGetFrameRate(), 2);
    //ofDrawBitmapStringHighlight(msg, 10, 10);
    ofDrawBitmapStringHighlight("use a s d w  to move", 10, 15);
    ofDrawBitmapStringHighlight("use q and z to look down or up", 10, 30);

    ofEnableDepthTest();
    ofEnableLighting();
    cam.begin();
    roadMaterial.begin();
    plane.draw();
    roadMaterial.end();
    treeMaterial.begin();
    for(auto tree : treeContainer){
        tree.draw();
    }
    treeMaterial.end();
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
