#pragma once
#include "ofMain.h"
#include "ofxLSBranch.h"

class ofxLSLine {
public:
    ofxLSLine();
    void generate(ofMesh& mesh, ofxLSBranch branch);
    
};
