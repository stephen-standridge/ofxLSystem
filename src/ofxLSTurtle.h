#pragma once

#include "ofMain.h"
#include "ofxLSBranch.h"
#include "ofxLSGeometry.h"
#include "ofxLSExecutor.h"
#include "ofxLSInstruction.h"
#include "ofxLSUtils.h"
#include "ofxLSGeometryAvailable.h"
#include "ofxLSBoundingBox.h"

class ofxLSTurtle : public ofxLSExecutor {
public:
    void setup( float moveLength, float width, float turnAngle, ofxLSGeometryAvailable geometry,
               bool randomYRotation, bool scaleWidth, int resolution, int textureRepeat);
    void generate(ofVboMesh& mesh, const string ruleStr, const int depth);
    BoundingBox getBuildedBoundingBox() const { return buildedBoundingBox; };
    void reset();

private:
    void createInstructions();
    const ofVec3f     origin = ofVec3f(0,0,0);
    float   defaultLength = 100;
    float   width;
    float   theta;
    ofxLSGeometryAvailable  geometry;
    bool    debug = false;
    bool    randomYRotation = false;
    bool    scaleWidth = false;
    int     resolution = 4;
    int     textureRepeat;
    ofVec3f position; // it can be removed?
    vector<string> getInstructionsFromString(string sentence);
    void maybeVectorExpandsBoundingBox(ofVec3f v);

    ofxLSGeometry                    geometryBuilder;
    
    
    //std::vector<shared_ptr<ofxLSBranch> > rBranchContainer;

    map<float, float> historySizes;
    pair<float, float> getPrevAndCurrentWidth(float currentLength);
    float getScaledWidth(float currentLength);

    void resetBoundingBox();
    BoundingBox buildedBoundingBox;
};
