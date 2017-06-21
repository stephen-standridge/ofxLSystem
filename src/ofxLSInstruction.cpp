#include "ofxLSInstruction.h"

ofxLSInstruction::ofxLSInstruction(string _text){
    //order is important, setHead needs to be called before setValue
    setHead(_text); // ex: 'A', '['
    setValues(_text);// ex: 0.9
};


string ofxLSInstruction::getHead() const {
    return head;
}

float ofxLSInstruction::getParam(int which, float fallback=0.0) const {
    if(params.size() < which + 1) {
        return fallback;
    }
    return ofToFloat(params[which]);
}

vector<string> ofxLSInstruction::getParams(){
    return params;
}

void ofxLSInstruction::setValues(string text){
    auto numberInRoundBrackets = ofxLSUtils::grepStringInRegex(text, "(\\([0-9\\.,]+\\)*)");
    
    params = ofxLSUtils::matchesInRegex(numberInRoundBrackets, "([0-9][0-9\\.]*,[ ])*[0-9][0-9\\.]*");
}

void ofxLSInstruction::setHead(string _text){
    head = ofxLSUtils::validTurtleInstruction(_text);
}
