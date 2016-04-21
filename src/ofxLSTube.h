#pragma once
#include "ofMain.h"
#include "ofxLSBranch.h"

class ofxLSTube {
public:
    ofxLSTube();
    void generate(ofMesh& mesh, const ofxLSBranch branch, const int radius,  const int scaledRadius);
    void setResolution(int _resolution){resolution = _resolution;};
private:
    int resolution = 32;
    bool semplifiedCap = true;
};
