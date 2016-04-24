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
    ofxLSystem();

    void setAxiom(string _axiom);
    void setRules(vector<string> _rulesContainer);
    void setTheta(float _theta);

    void setResolution(int _resolution)               {resolution = _resolution;};
    void setRandomZRotation(bool _randomZRotation)    { randomZRotation = _randomZRotation; };
    void setGeometry(ofxLSGeometryAvailable _geometry){ofxLSGeometryAvailable geometry = _geometry;};
    void setStep(int _depth)                          { depth = _depth; };
    void setScaleWidth(bool _scaleWidht)              { scaleWidth = _scaleWidht; };
    void setStepWidth(float _stepWidth)               { stepWidth = _stepWidth; };
    void setStepLength(float _stepLength)             { stepLength = _stepLength; };
    void setConstants(map<string,float> _Constants)   { constants = _Constants; };

    void build();
    // i've to redifine this method because i can not get it working
    // that one inherited from of3DPrimive, i get this warning of3dPrimitive: drawNormals(): mesh normals are disabled
    void drawNormals( float length, bool bFaceNormals=false ) const;
private:

    vector<string>    rulesContainer = {"F -> F[+F][-F]"};
    string            axiom = "F";
    bool              randomZRotation = false;
    ofxLSGeometryAvailable geometry = TUBES;
    int               resolution = 10;
    int               depth = 1;
    float             theta = 25.00;
    float             stepWidth = 10.00;
    bool              scaleWidth = false;
    float             stepLength = 100.00;
    map<string,float> constants = Constants();
    ofxLSTurtle       turtle;
    ofVboMesh         mesh;
    mutable ofMesh    normalsMesh;

    void              setMeshMode(ofxLSGeometryAvailable geometry);

    //validations
    bool thetaValueIsinRange(float theta);
    bool isAxiomInRules(string _axiom, vector<string> _strRules);
    void validateInput(string _axiom, vector<string> _strRules, float theta);
};
