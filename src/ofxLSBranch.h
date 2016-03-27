#pragma once
#include "ofMain.h"

class ofxLSBranch {
public:
    ofxLSBranch(const ofNode _begin, const ofNode _end){
        begin = _begin;
        end = _end;
    };
    ofNode begin;
    ofNode end;
};
