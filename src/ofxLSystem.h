#pragma once

#include "ofMain.h"
#include "ofxLSystemGrammar.h"
#include "ofxLSInputError.h"
#include "ofxLSUtils.h"

typedef map<string,float> Constants;

class ofxLSystem {
public:
    ofxLSystem(string _axiom = "F", vector<string> _rules = {"F -> F[+F][-F]"}, int _depth=1);
    void setup();
    
    void setAxiom(string _axiom);
    void setRules(vector<string> _rulesContainer);
    void setConstants(map<string,float> _Constants)   { constants = _Constants; };
    void setStep(int _depth)                          { depth = _depth; };
    int  getStep()                                    { return depth; };

    bool isParametric()                               { return ofxLSystemGrammar::detectGrammarType(rulesContainer) != "parametric"; };
    string back()                                     { return currentSentences.back(); };
    string at(int index)                              { return currentSentences.at(index); };

private:
    vector<string>    currentSentences;
    vector<string>    rulesContainer;
    string            axiom;
    int               depth;
    map<string,float> constants = Constants();

    //validations
    bool isAxiomInRules(string _axiom, vector<string> _strRules);
    bool validateInput(string _axiom, vector<string> _strRules);
};
