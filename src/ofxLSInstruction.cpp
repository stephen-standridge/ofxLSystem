#include "ofxLSInstruction.h"

 ofxLSInstruction::ofxLSInstruction(string _text){
    //order is important, setHead needs to be called before setValue
    setHead(_text); // ex: 'A', '['
    setValues(_text);// ex: 0.9
};


string ofxLSInstruction::getHead() const {
    return head;
}

float ofxLSInstruction::getAngle(float defaultValue) const {
    if (angleIsProvided) {
        return angle;
    }else{
        return defaultValue;
    }
}

float ofxLSInstruction::getLength(float defaultValue) const {
    if (lengthIsProvided) {
        return length;
    }else{
        return defaultValue;
    }
}

void ofxLSInstruction::setValues(string text){
    auto numberInRoundBrackets = ofxLSUtils::grepStringInRegex(text, "(\\([0-9\\.,]+\\)*)");
    if (numberInRoundBrackets.length()>2) {
        // TODO, acctually we handle only single number, like (0.9). not multiple numbers like
        // (0.2, 1.4). In this last case, we take only 0.2
        auto stringValue = ofxLSUtils::grepStringInRegex(text, "([0-9\\.]+)");
        if(head == "\\" || head == "/" || head == "&" || head == "^" || head == "+" || head == "-" || head == "|" ){
            angleIsProvided = true;
            angle = ofToFloat(stringValue);
        }else{
            lengthIsProvided = true;
            length = ofToFloat(stringValue);
        }
    }else{
        lengthIsProvided = false;
        angleIsProvided = false;
    }
}

void ofxLSInstruction::setHead(string _text){
    head = ofxLSUtils::grepStringInRegex(_text, "([A-Z|\\^|&|\\+|\\-|\\?|\\||\\]|\\[|/|\\\\])");
}
