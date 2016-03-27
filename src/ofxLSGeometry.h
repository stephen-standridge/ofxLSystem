#pragma once
#include "ofMain.h"
#include "ofxLSBranch.h"
#include "ofxLSTube.h"
#include "ofxLSTubeDeformed.h"
#include "ofxLSLine.h"

class ofxLSGeometry{
public:
    void putIntoMesh(const ofxLSBranch branch, ofVboMesh& mesh, const float width, const string _geometryType);
    
private:
    //avoid to save values in instance vars in these classes, they should simply
    // add stuff into the mesh
    ofxLSTube tube;
    ofxLSTubeDeformed tubeDeformed;
    ofxLSLine line;
};
