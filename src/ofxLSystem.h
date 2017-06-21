#pragma once

#include "ofMain.h"
#include "ofxLSystemGrammar.h"
#include "ofxLSUtils.h"

#include "ofxLSBuilder.h"
#include "ofxLSTurtle.h"

class ofxLSystem : public ofxLSTurtle {
private:
    ofxLSBuilder            lsystem;
    
public:
    void reset();
    void build(int _sentenceIndex = -1);
    
    void setAxiom(string _axiom)                    { lsystem.setAxiom(_axiom); };
    void setRules(vector<string> _rules)            { lsystem.setRules(_rules); };
    void setConstants(map<string,float> _constants) { lsystem.setConstants(_constants); };
    void setStep(int _depth)                        { lsystem.setStep(_depth); };
    int  getStep()                                  { return lsystem.getStep(); };
    
};
