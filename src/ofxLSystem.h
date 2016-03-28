#pragma once

#include "ofMain.h"
#include "ofxLSTurtle.h"
#include "ofxLSystemGrammar.h"
#include "ofxLSGeometryAvailable.h"

typedef map<string,float> Constants;

class ofxLSystem {
public:
    void setup(
               string axiom,
               vector<string> rules,
               int depth = 2,
               float theta = 25.00,
               ofVec3f position = ofVec3f(0, 0, 0),
               map<string, float> _constants = Constants(),
               bool randomZRotation = true,
               ofxLSGeometryAvailable geometry = TUBES);
    void build();
    void drawFaces();
    void drawWireframe();
    void draw();
    void drawNormals( float length, bool bFaceNormals=false ) const;

private:
    void              setMeshMode(ofxLSGeometryAvailable geometry);
    vector<string>    rulesContainer;
    string            axiom = "F";
    bool              randomZRotation = false;
    int               depth = 1;
    float             theta = 25.00;
    map<string,float> constants;
    ofxLSTurtle       turtle;
    ofVboMesh         mesh;
    mutable ofMesh    normalsMesh;
};
