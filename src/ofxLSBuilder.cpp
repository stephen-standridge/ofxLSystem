#include "ofxLSBuilder.h"

ofxLSBuilder::ofxLSBuilder(string _axiom, vector<string> _rules, int _depth){
    //check if axiom, rules and theta are ok,
    // if not, define some default
    if(validateInput(_axiom, _rules)) {
        axiom = _axiom;
        rulesContainer = _rules;
    }
    depth = _depth;
}

void ofxLSBuilder::setAxiom(string _axiom){
    axiom = _axiom;
};

void ofxLSBuilder::setRules(vector<string> _rulesContainer){
    rulesContainer = _rulesContainer;
};

void ofxLSBuilder::setup() {
    reset();
    build();
}

void ofxLSBuilder::reset() {
    currentSentences.clear();
}

void ofxLSBuilder::build() {
    currentSentences = ofxLSystemGrammar::buildSentences(rulesContainer, depth, axiom, constants);
}

bool ofxLSBuilder::isAxiomInRules(string _axiom, vector<string> _rulesContainer){
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

bool ofxLSBuilder::validateInput(string _axiom, vector<string> _strRules){
    try {
        if(!isAxiomInRules(_axiom, _strRules)){
            throw ofxLSBuilderError("axiom is not in rules container");
        }
    } catch (ofxLSBuilderError& e) {
        ofLogError(e.what());
        axiom = "F";
        rulesContainer = {"F -> F[+F][-F]"};
        return false;
    }
    return true;
}
