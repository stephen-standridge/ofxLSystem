#include "ofxLSystem.h"

void ofxLSystem::setup() {
    lsystem.setup();
    ofxLSTurtle::setup();
    
}

void ofxLSystem::build(int _sentenceIndex) {
    string sentence;
    
    if (_sentenceIndex < 0) {
        //by default build the last sentence
        if(lsystem.size() != getStep()) {
            lsystem.build();
        }
        sentence = lsystem.back();
    } else {
        sentence = lsystem.at(_sentenceIndex);
        if (sentence.length() <= 0 && getStep() > _sentenceIndex) {
            lsystem.build();
            sentence = lsystem.at(_sentenceIndex);
        }
    }
    buildSentence(sentence);
}
