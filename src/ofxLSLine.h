#pragma once
#include "ofMain.h"
#include "ofxLSBranch.h"

class ofxLSLine {
public:
    ofxLSLine();
    static const ofPrimitiveMode meshMode = OF_PRIMITIVE_LINES;
    void putIntoMesh(const ofxLSBranch branch, ofVboMesh& mesh, int resolution, float length, int textureRepeat);
    void generate(ofMesh& mesh, ofxLSBranch branch);
    
};
