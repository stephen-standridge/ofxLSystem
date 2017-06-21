#include "ofxLSystem.h"

ofxLSystem::ofxLSystem(string _axiom, vector<string> _rules, int _depth){
    if(validateInput(_axiom, _rules)) {
        axiom = _axiom;
        rulesContainer = _rules;
    }
    depth = _depth;
}

void ofxLSystem::setAxiom(string _axiom){
    axiom = _axiom;
};

void ofxLSystem::setRules(vector<string> _rulesContainer){
    rulesContainer = _rulesContainer;
};

void ofxLSystem::setup() {
    //check if axiom, rules and theta are ok,
    // if not, define some default
    
    //clear the sentences
    currentSentences.clear();
    currentSentences = ofxLSystemGrammar::buildSentences(rulesContainer, depth, axiom, constants);
}

bool ofxLSystem::isAxiomInRules(string _axiom, vector<string> _rulesContainer){
    auto lettersInAxiom = ofxLSUtils::matchesInRegex(_axiom, "[a-zA-Z]");
    for(auto letter : lettersInAxiom){
        for(string rule : _rulesContainer){
            if(ofxLSUtils::countSubstring(rule, letter) > 0){
                return true;
            }
        }
    }

    return false;
}

bool ofxLSystem::validateInput(string _axiom, vector<string> _strRules){
    try {
        if(!isAxiomInRules(_axiom, _strRules)){
            throw ofxLSInputError("axiom is not in rules container");
        }
    } catch (ofxLSInputError& e) {
        ofLogError(e.what());
        axiom = "F";
        rulesContainer = {"F -> F[+F][-F]"};
        return false;
    }
    return true;
}
