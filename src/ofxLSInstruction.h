#pragma once
#include "ofMain.h"
#include "ofxLSUtils.h"

class ofxLSInstruction{
public:
    ofxLSInstruction(string str);
    string getHead() const;
    float getAngle(float defaultValue) const;
    float getLength(float defaultValue) const;
private:
    string text;
    string head;
    bool angleIsProvided = false;
    bool lengthIsProvided = false;
    float angle = 0.0;
    float length = 0.0;
    void setValues(string text);
    void setHead(string text);
};
