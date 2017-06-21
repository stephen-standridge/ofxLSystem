#pragma once
#include "ofMain.h"
#include "ofxLSUtils.h"

class ofxLSInstruction{
public:
    ofxLSInstruction(string str);
    string getHead() const;
    float getParam(int which, float fallback) const;
    vector<string> getParams();
    
private:
    string text;
    string head;
    vector<string> params;
    void setValues(string text);
    void setHead(string text);
};
