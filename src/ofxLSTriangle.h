#pragma once
#include "ofMain.h"
#include "ofxLSBranch.h"

class ofxLSTriangle {
public:
    ofxLSTriangle();
    
    static const ofPrimitiveMode meshMode = OF_PRIMITIVE_LINES;
    
    void putIntoMesh(const ofxLSBranch branch, ofVboMesh& mesh, int resolution, float length, int textureRepeat);
    void generate(ofMesh& mesh, const ofxLSBranch branch, const float length);
    void setResolution(int _resolution){resolution = _resolution;};
private:
    int resolution = 7;
};
