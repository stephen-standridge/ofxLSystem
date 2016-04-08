#pragma once

#include "ofMain.h"
#include "ofxLSBranch.h"
#include "ofxLSGeometry.h"
#include "ofxLSInstruction.h"
#include "ofxLSUtils.h"
#include "ofxLSGeometryAvailable.h"

class ofxLSTurtle {
public:
    void setup( float moveLength, float width, float turnAngle, ofxLSGeometryAvailable geometry,
               bool randomZRotation = false, bool scaleWidth = false);
    void generate(ofVboMesh& mesh, const string ruleStr, const int depth);
private:
    const ofVec3f     origin = ofVec3f(0,0,0);
    float   defaultLength = 100;
    float   width;
    float   theta;
    ofxLSGeometryAvailable  geometry;
    bool    debug = false;
    bool    randomZRotation = false;
    bool    scaleWidth = false;
    ofVec3f position; // it can be removed?
    vector<string> getInstructionsFromString(string sentence);

    ofxLSGeometry                    geometryBuilder;
    std::vector<shared_ptr<ofNode> > bookmarks;
    std::vector<shared_ptr<ofNode> > branchContainer;

    float getScaledWidth(float currentLength);
};
