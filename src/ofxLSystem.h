#pragma once

#include "ofMain.h"
#include "ofxLSTurtle.h"
#include "ofxLSystemGrammar.h"
#include "ofxLSGeometryAvailable.h"
#include "ofxLSInputError.h"
#include "of3dPrimitives.h"

typedef map<string,float> Constants;

class ofxLSystem  : public of3dPrimitive{
public:
    void setup(
               string axiom,
               vector<string> rules,
               int depth = 2,
               float theta = 25.00,
               float stepWidth = 10.00,
               float stepLength = 100.00,
               ofVec3f position = ofVec3f(0, 0, 0),
               map<string, float> _constants = Constants(),
               bool randomZRotation = true,
               ofxLSGeometryAvailable geometry = TUBES);

    //begin setup method overloading
    void setup(
               string axiom,
               vector<string> rules,
               int depth = 2,
               float theta = 25.00,
               ofVec3f position = ofVec3f(0, 0, 0),
               map<string, float> _constants = Constants(),
               bool randomZRotation = true,
               ofxLSGeometryAvailable geometry = TUBES);

    void setup(
               string axiom,
               vector<string> rules,
               int depth = 2,
               float theta = 25.00,
               float stepWidth = 10.00,
               float stepLength = 100.00,
               ofVec3f position = ofVec3f(0, 0, 0));
    //end setup method overloading

    void build();
    // i've to redifine this method because i can not get it working
    // that one inherited from of3DPrimive, i get this warning of3dPrimitive: drawNormals(): mesh normals are disabled
    void drawNormals( float length, bool bFaceNormals=false ) const;

private:
    void              setMeshMode(ofxLSGeometryAvailable geometry);
    vector<string>    rulesContainer;
    string            axiom = "F";
    bool              randomZRotation = false;
    int               depth = 1;
    float             theta = 25.00;
    float             stepWidth = 10.00;
    float             stepLength = 100.00;
    map<string,float> constants;
    ofxLSTurtle       turtle;
    ofVboMesh         mesh;
    mutable ofMesh    normalsMesh;

    //validations
    bool thetaValueIsinRange(float theta);
    bool isAxiomInRules(string _axiom, vector<string> _strRules);
    void validateInput(string _axiom, vector<string> _strRules, float theta);
};
