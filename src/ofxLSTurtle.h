#pragma once

#include "ofMain.h"
#include "ofxLSTurtle.h"
#include "ofxLSBranch.h"
#include "ofxLSGeometry.h"
#include "ofxLSInstruction.h"
#include "ofxLSUtils.h"
#include "ofxLSGeometryAvailable.h"

class ofxLSTurtle {
public:
    void setup( float moveLength, float width, float turnAngle, ofxLSGeometryAvailable geometry, const ofVec3f pos, bool randomZRotation = false);
    void generate(ofVboMesh& mesh, const string ruleStr, const int depth);
private:
    float   defaultLength = 100;
    float   width;
    float   theta;
    ofxLSGeometryAvailable  geometry;
    bool    debug = false;
    bool    randomZRotation = false;
    ofVec3f position;
    vector<string> getInstructionsFromString(string sentence);

    ofxLSGeometry                    geometryBuilder;
    std::vector<shared_ptr<ofNode> > bookmarks;
    std::vector<shared_ptr<ofNode> > branchContainer;
};
