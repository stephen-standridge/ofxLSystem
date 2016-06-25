#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableAlphaBlending();
    ofEnableDepthTest();
    light.enable();
    light.setPosition(ofVec3f(400,300,200));
    light.lookAt(ofVec3f(0,0,0));
    //important, ofDisableArbText has to be called before the image is loaded
    ofDisableArbTex();
    string textureName = "texture.png";

    // first texture
    ofLoadImage(bark, textureName);

    // second texture
    ofLoadImage(bark2, textureName);
    bark2.setTextureWrap(GL_REPEAT, GL_REPEAT);
    bark2.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

    // third texture
    ofLoadImage(bark3,textureName);
    bark3.setTextureWrap(GL_REPEAT, GL_REPEAT);
    bark3.generateMipmap(); // it creates a mipmap out of that image
    bark3.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST); //activate mipmap filtering once texture has been loaded

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
    tree.truck(-300);

    // tree on which a texture will be repeated N times
    tree2.setAxiom("A(100)");
    tree2.setRules({"A(s) -> F(s)[+A(s/R)][-A(s/R)]"});
    tree2.setRandomYRotation(true);
    tree2.setConstants(constants);
    // here is is defined how many times is the texture repeated
    tree2.setTextureRepeat(6);
    tree2.setStep(8);
    tree2.setScaleWidth(true);
    tree2.setStepWidth(21.5);
    tree2.setStepLength(100);
    tree2.build();

    // tree on which a texture will be repeated N times using a mipmap
    // note how the border of the black circles are antialiased
    // try to change GL_LINEAR_MIPMAP_LINEAR to GL_NEAREST
    // and see how it changes
    tree3.setAxiom("A(100)");
    tree3.setRules({"A(s) -> F(s)[+A(s/R)][-A(s/R)]"});
    tree3.setRandomYRotation(true);
    tree3.setConstants(constants);
    tree3.setStep(8);
    tree3.setTextureRepeat(6);
    tree3.setScaleWidth(true);
    tree3.setStepWidth(21.5);
    tree3.setStepLength(100);
    tree3.build();
    tree3.truck(300);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

    bark.bind();
    tree.draw();
    bark.unbind();

    bark2.bind();
    tree2.draw();
    bark2.unbind();

    bark3.bind();
    tree3.draw();
    bark3.unbind();

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
