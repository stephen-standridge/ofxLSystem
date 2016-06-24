#pragma once
#include "ofMain.h"
#include "ofxLSBranch.h"

class ofxLSTube {
public:
    ofxLSTube();
    void generate(ofMesh& mesh, const ofxLSBranch branch, const float length);
    void setResolution(int _resolution){resolution = _resolution;};
private:
    int resolution = 32;
    int textureRepeat = 1;
};
