#pragma once

#include "ofMain.h"
#include "ofxLSystem.h"
#include "ofxLSBranch.h"
#include "ofxLSGeometry.h"
#include "ofxLSExecutor.h"
#include "ofxLSUtils.h"
#include "ofxLSGeometryAvailable.h"
#include "ofxLSBoundingBox.h"

class ofxLSTurtle : public of3dPrimitive{
public:
    ofxLSTurtle(float moveLength, float width, float turnAngle, ofxLSGeometryAvailable geometry,
                bool randomYRotation, bool scaleWidth, int resolution, int textureRepeat);
    void setup();
    void reset();
    void save(string filename);
    
    void setTheta(float _theta)                       { theta = _theta; };
    void setResolution(int _resolution)               { resolution = _resolution; };
    void setTextureRepeat(int _n)                     { textureRepeat = _n; };
    void setRandomYRotation(bool _randomYRotation)    { randomYRotation = _randomYRotation; };
    void setGeometry(ofxLSGeometryAvailable _geometry){ geometry = _geometry; };
    void setScaleWidth(bool _scaleWidht);
    void setStepWidth(float _stepWidth)               { stepWidth = _stepWidth; };
    void setStepLength(float _stepLength)             { stepLength = _stepLength; };
    
    void computeBoundingBox();
    BoundingBox getBoundingBox() const                { return boundingBox; };
    
    void build(int sentenceIndex=-1);

private:
    ofxLSExecutor           executor;
    ofxLSystem              lsystem;
    ofVboMesh               mesh;
    BoundingBox             boundingBox;
    BoundingBox             buildedBoundingBox;
    ofxLSGeometryAvailable  geometry = TUBES;
    ofxLSGeometry           geometryBuilder;

    map<float, float>       historySizes;

    // geometry/space
    const ofVec3f origin = ofVec3f(0,0,0);
    float         stepWidth = 10.00;
    float         stepLength = 100.00;
    float         theta = 25.00;
    
    // options
    
    bool    debug = false;
    bool    randomYRotation = false;
    bool    scaleWidth = false;
    int     resolution = 10;
    int     textureRepeat = 1;

    void  setMeshMode(ofxLSGeometryAvailable geometry);
    
    pair<float, float> getPrevAndCurrentWidth(float currentLength);
    float getScaledWidth(float currentLength);
    
    void  createInstructions();
    void  resetBoundingBox();
    void  maybeVectorExpandsBoundingBox(ofVec3f v);
    bool  validateInput(float theta);
};
