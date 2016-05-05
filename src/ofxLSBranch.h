#pragma once
#include "ofMain.h"

class ofxLSBranch {
public:
    ofxLSBranch(const ofNode _begin, const ofNode _end, pair<float, float> _capSizes){
        //Imagine a cylinder
        begin = _begin; // it is where the cylinder starts
        end = _end;     // it is where the cylinder ends
        capSizes = _capSizes; // the length of the ray of the 2 caps of the cylinder
        // the first one defines the bottom cap, the second one defines top cap
    };
    ofNode begin;
    ofNode end;
    pair<float, float> capSizes;
};
