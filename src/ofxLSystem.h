#pragma once

#include "ofMain.h"
#include "ofxLSTurtle.h"
#include "ofxLSystemGrammar.h"
#include "ofxLSGeometryAvailable.h"
#include "ofxLSInputError.h"
#include "of3dPrimitives.h"
#include "ofxLSBoundingBox.h"

typedef map<string,float> Constants;

class ofxLSystem  : public of3dPrimitive{
public:
    ofxLSystem();

    void setAxiom(string _axiom);
    void setRules(vector<string> _rulesContainer);
    void setTheta(float _theta);

    void setResolution(int _resolution)               { resolution = _resolution; };
    void setTextureRepeat(int _n)                     { textureRepeat = _n; };
    void setRandomYRotation(bool _randomYRotation)    { randomYRotation = _randomYRotation; };
    void setGeometry(ofxLSGeometryAvailable _geometry){ geometry = _geometry; };
    void setStep(int _depth)                          { depth = _depth; };
    void setScaleWidth(bool _scaleWidht);
    void setStepWidth(float _stepWidth)               { stepWidth = _stepWidth; };
    void setStepLength(float _stepLength)             { stepLength = _stepLength; };
    void setConstants(map<string,float> _Constants)   { constants = _Constants; };
    void computeBoundingBox();
    BoundingBox getBoundingBox() const;
    void setBoundingBox(BoundingBox);

    void build();
    void save(string filename);

private:

    vector<string>    rulesContainer = {"F -> F[+F][-F]"};
    string            axiom = "F";
    bool              randomYRotation = false;
    ofxLSGeometryAvailable geometry = TUBES;
    int               resolution = 10;
    int               depth = 1;
    float             theta = 25.00;
    float             stepWidth = 10.00;
    bool              scaleWidth = false;
    float             stepLength = 100.00;
    int               textureRepeat = 1;
    map<string,float> constants = Constants();
    ofxLSTurtle       turtle;
    ofVboMesh         mesh;
    BoundingBox       boundingBox;

    void              setMeshMode(ofxLSGeometryAvailable geometry);

    //validations
    bool thetaValueIsinRange(float theta);
    bool isAxiomInRules(string _axiom, vector<string> _strRules);
    void validateInput(string _axiom, vector<string> _strRules, float theta);
};
