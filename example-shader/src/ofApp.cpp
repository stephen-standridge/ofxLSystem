#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableAlphaBlending();
    ofEnableDepthTest();
    light.setup();
    light.enable();
    light.setPosition(ofVec3f(400,300,200));
    light.lookAt(ofVec3f(0,0,0));

    map<string, float> constants;
    constants.insert(make_pair("R", 1.456));

    // tree on which it will be applied a texture
    tree.setAxiom("A(100)");
    tree.setRules({"A(s) -> F(s)[+A(s/R)][-A(s/R)]"});
    tree.setRandomYRotation(true);
    tree.setConstants(constants);
    tree.setStep(8);
    tree.setScaleWidth(true);
    tree.setStepWidth(21.5);
    tree.setStepLength(100);
    tree.build();

    if(ofIsGLProgrammableRenderer()){
        //I'm using opengl 4.1 that support the programmable pipeline
        //shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
        shader.load("shaders_gl3/colors.vert", "shaders_gl3/colors.frag");
    }

    gui.setup();
    gui.add(scale.set("scale", 10.f, 1.f, 20.f));
    ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

    shader.begin();
    shader.setUniform1f("uTime", ofGetElapsedTimef());
    shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );


    tree.draw();
    shader.end();
    cam.end();

    maybeDrawGui();
}

void ofApp::maybeDrawGui(){
    if(drawGui){
        ofDisableDepthTest();
        gui.draw();
        ofEnableDepthTest();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g'){
        drawGui = !drawGui;
    }
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
