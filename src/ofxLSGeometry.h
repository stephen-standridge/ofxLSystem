#pragma once
#include "ofMain.h"
#include "ofxLSBranch.h"
#include "ofxLSTube.h"
#include "ofxLSTubeDeformed.h"
#include "ofxLSLine.h"
#include "ofxLSGeometryAvailable.h"

class ofxLSGeometry{
public:
    void putIntoMesh(const ofxLSBranch branch, ofVboMesh& mesh, const float width, const float scaledWidth, ofxLSGeometryAvailable _geometryType, int resolution);
    
private:
    //avoid to save values in instance vars in these classes, they should simply
    // add stuff into the mesh
    ofxLSGeometryAvailable geometry;
    ofxLSTube tube;
    ofxLSTubeDeformed tubeDeformed;
    ofxLSLine line;
};
