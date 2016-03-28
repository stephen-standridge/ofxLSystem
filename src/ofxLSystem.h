#pragma once

#include "ofMain.h"
#include "ofxLSTurtle.h"
#include "ofxLSystemGrammar.h"

typedef map<string,float> Constants;

class ofxLSystem {
public:
    void setup(
               int depth,
               string axiom,
               float theta,
               vector<string> rules,
               ofVec3f position,
               map<string, float> _constants = Constants(),
               bool randomYRotation = true,
               string geometry = "tube");
    void build();
    void drawFaces();
    void drawWireframe();
    void draw();
    void drawNormals( float length, bool bFaceNormals=false ) const;

private:
    void              setMeshMode(string geometry);
    vector<string>    rulesContainer;
    string            axiom = "F";
    bool              randomYRotation = false;
    int               depth = 0;
    float             theta = 20;
    map<string,float> constants;
    ofxLSTurtle       turtle;
    ofVboMesh         mesh;
    mutable ofMesh    normalsMesh;
};
