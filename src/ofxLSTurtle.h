#pragma once

#include "ofMain.h"
#include "ofxLSBranch.h"
#include "ofxLSGeometry.h"
#include "ofxLSExecutor.h"
#include "ofxLSUtils.h"
#include "ofxLSGeometryAvailable.h"
#include "ofxLSBoundingBox.h"

class ofxLSTurtleError : public exception {
public:
    ofxLSTurtleError(string m="exception!") : msg(m) {}
    ofxLSTurtleError() throw() {}
    const char* what() const throw() { return msg.c_str(); }
    
private:
    string msg;
};


class ofxLSTurtle : public of3dPrimitive {
public:
    ofxLSTurtle(float moveLength = 100.00, float width = 10.00, float turnAngle=25.00, ofxLSGeometryAvailable geometry=TUBES, bool randomYRotation=false, bool scaleWidth=false, int resolution=10, int textureRepeat=1);
    void setup();
    void reset();
    void buildSentence(string _sentenceToBuild);
    void save(string _filename);
    
    void setTheta(float _theta)                       { theta = _theta; };
    void setResolution(int _resolution)               { resolution = _resolution; };
    void setTextureRepeat(int _n)                     { textureRepeat = _n; };
    void setRandomYRotation(bool _randomYRotation)    { randomYRotation = _randomYRotation; };
    void setGeometry(ofxLSGeometryAvailable _geometry){ geometry = _geometry; };
    void setScaleWidth(bool _scaleWidth)              { scaleWidth = _scaleWidth; };
    void setStepWidth(float _stepWidth)               { stepWidth = _stepWidth; };
    void setStepLength(float _stepLength)             { stepLength = _stepLength; };
    
    void computeBoundingBox();
    BoundingBox getBoundingBox() const                { return boundingBox; };
    
private:
    ofxLSExecutor           executor;
    ofVboMesh               mesh;
    BoundingBox             boundingBox;
    BoundingBox             buildedBoundingBox;
    ofxLSGeometryAvailable  geometry;
    ofxLSGeometry           geometryBuilder;

    map<float, float>       historySizes;

    // geometry/space
    const ofVec3f origin = ofVec3f(0,0,0);
    float         stepWidth;
    float         stepLength;
    float         theta;
    
    // options
    
    bool    debug = false;
    bool    randomYRotation;
    bool    scaleWidth;
    int     resolution;
    int     textureRepeat;

    void  setMeshMode(ofxLSGeometryAvailable geometry);
    
    pair<float, float> getPrevAndCurrentWidth(float currentLength);
    float getScaledWidth(float currentLength);
    
    void  createInstructions();
    void  resetBoundingBox();
    void  maybeVectorExpandsBoundingBox(ofVec3f v);
    bool  validateInput(float theta);
};
