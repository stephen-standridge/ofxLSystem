#pragma once
#include "ofMain.h"
#include "ofxLSBranch.h"

class ofxLSTube {
public:
    ofxLSTube();
    static const ofPrimitiveMode meshMode = OF_PRIMITIVE_TRIANGLES;

    void generate(ofMesh& mesh, const ofxLSBranch branch, const float length);
    void setResolution(int _resolution);
    void setTextureRepeat(int _n){textureRepeat = _n;};
    void putIntoMesh(const ofxLSBranch branch, ofVboMesh& mesh, int resolution, float length, int textureRepeat);
private:
    int resolution = 32;
    int textureRepeat = 1;
};
