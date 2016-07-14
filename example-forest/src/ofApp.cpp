#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    float halfScreen = ofGetWidth()/2;
    //light
    light.setPosition(500, 1000, 1600);
    light.enable();

    //camera
    cam.setPosition(0, 100, 600);
    cam.lookAt(ofVec3f(0, 0, 0));
    //cam.setNearClip(0.01f);
    //cam.setMovementMaxSpeed( 25.f );

    //plane
    plane.setPosition(100, 0, 0);
    plane.set(20000, 20000);
    plane.setResolution(20, 20);
    plane.rotate(270, 1, 0 , 0);

    roadMaterial.setDiffuseColor(ofFloatColor::moccasin);
    roadMaterial.setShininess(0.01);
    treeMaterial.setAmbientColor(ofFloatColor::hotPink);
    treeMaterial.setSpecularColor(ofFloatColor::blueSteel);
    treeMaterial.setShininess(0.04);
    map<string, float> constants;
    constants.insert(make_pair("R", 1.356));

    for(int i = 0; i<nTree; i++){
        ofxLSystem tree;
        tree.setAxiom("A(100)");
        tree.setRules({"A(s) -> F(s)[+A(s/R)][-A(s/R)]"});
        tree.setRandomYRotation(true);
        tree.setConstants(constants);
        tree.setStep(abs(ofRandom(5, 10)));
        tree.setScaleWidth(true);
        tree.setStepWidth(abs(ofRandom(30.5, 40.5)));
        tree.setStepLength(abs(ofRandom(150,300)));
        tree.build();
        auto pos = ofVec2f(ofRandom(-halfScreen, halfScreen),
                           ofRandom(-halfScreen, halfScreen));
        for (int i=0; i<tree.getMesh().getNumVertices(); i++) {
            tree.getMesh().getVerticesPointer()[i] += ofVec3f(pos.x, 0, pos.y);
        }
        forest.append(tree.getMesh());
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

    ofEnableDepthTest();
    ofEnableLighting();
    cam.begin();
    roadMaterial.begin();
    plane.draw();
    roadMaterial.end();
    treeMaterial.begin();
    forest.draw();
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
