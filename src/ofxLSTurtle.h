#pragma once

#include "ofMain.h"
#include "ofxLSBranch.h"
#include "ofxLSGeometry.h"
#include "ofxLSExecutor.h"
#include "ofxLSUtils.h"
#include "ofxLSGeometryAvailable.h"
#include "ofxLSBoundingBox.h"
#include "ofxLSTube.h"
#include "ofxLSTubeDeformed.h"
#include "ofxLSTriangle.h"
#include "ofxLSLine.h"

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
    ofxLSTurtle(float moveLength = 100.00, float width = 10.00, float turnAngle=25.00, ofxLSGeometryAvailable geometry=TUBES, bool randomYRotation=false, bool scaleWidth=false, int _resolution=10, int textureRepeat=1);
    void setup();
    void reset();
    void buildSentence(string _sentenceToBuild);
    void save(string _filename);
    
    void setTheta(float _theta)                       { theta = _theta; };
    void setResolution(int _resolution)               { resolution = _resolution; };
    void setTextureRepeat(int _n)                     { textureRepeat = _n; };
    void setRandomYRotation(bool _randomYRotation)    { randomYRotation = _randomYRotation; };
    void setScaleWidth(bool _scaleWidth)              { scaleWidth = _scaleWidth; };
    void setStepWidth(float _stepWidth)               { stepWidth = _stepWidth; };
    void setStepLength(float _stepLength)             { stepLength = _stepLength; };
    
    float getTheta()                                   { return theta; };
    int   getResolution()                              { return resolution; };
    bool  getTextureRepeat()                           { return textureRepeat; };
    bool  getRandomYRotation()                         { return randomYRotation; };
    bool  getScaleWidth()                              { return scaleWidth; };
    float getStepWidth()                               { return stepWidth; };
    float getStepLength()                              { return stepLength; };
    ofxLSGeometryAvailable getGeometryType()           { return geometry; };
    
    void  computeBoundingBox();
    void  resetBoundingBox();
    void  maybeVectorExpandsBoundingBox(ofVec3f v);
    BoundingBox getBoundingBox() const                { return boundingBox; };
    void  setMeshMode(ofxLSGeometryAvailable geometry);
    pair<float, float> getPrevAndCurrentWidth(float currentLength);
    float getScaledWidth(float currentLength);
    
    bool  validateInput(float theta);

    void createInstructions();
    void createRoot();
    
    ofxLSExecutor<ofNode>   executor;
    ofxLSGeometry           geometryBuilder;
    ofVboMesh               mesh;

private:
    //bounding box
    BoundingBox             boundingBox;
    BoundingBox             buildedBoundingBox;
    
    //geometry generation
    ofxLSGeometryAvailable  geometry;
    ofxLSTube tube;
    ofxLSTubeDeformed tubeDeformed;
    ofxLSLine line;
    ofxLSTriangle triangle;
    void putIntoMesh(const ofxLSBranch branch);

    map<float, float>       historySizes;

    // geometry/space
    float         stepWidth;
    float         stepLength;
    float         theta;
    
    // options
    bool    debug = false;
    bool    randomYRotation;
    bool    scaleWidth;
    int     resolution;
    int     textureRepeat;


};
