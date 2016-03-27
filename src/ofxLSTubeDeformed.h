#pragma once
#include "ofMain.h"
#include "ofxLSBranch.h"

class ofxLSTubeDeformed {
public:
    ofxLSTubeDeformed();
    void generate(ofMesh& mesh, const ofxLSBranch branch, const int radius);
private:
    int resolution = 4;
    float radius = 20.00;
    float side = 1.0;
    float variation = side /2;
    void build(const int resolution);
    void buildRing(const int resolution);
    void calcSide();
    void calcNormals(ofMesh& mesh);
    void generateSetRandomNumbers(const unsigned int resolution);
    void addRoundIndices(const int resolution, const int totVertices, ofMesh& mesh);

    vector<ofVec3f> ring;
    vector<float> randomNumbers;
    vector<ofVec3f> middleRing;
};
