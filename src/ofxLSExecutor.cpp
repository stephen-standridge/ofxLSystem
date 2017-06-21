//
//  ofxLSExecutor.cpp
//  example-shader
//
//  Created by kevin ambrosia on 6/20/17.
//
//

#include "ofxLSExecutor.h"

void ofxLSExecutor::pushNode(shared_ptr<ofNode> node) {
    if(node != NULL) {
        bookmarks.push_back(node);
    } else {
        bookmarks.push_back(branchContainer.back());
    }
}

void ofxLSExecutor::popNode() {
    bookmarks.pop_back();
}

void ofxLSExecutor::reset() {
    bookmarks.clear();
    branchContainer.clear();
}

shared_ptr<ofNode> ofxLSExecutor::back(){
    return branchContainer.back();
}

shared_ptr<ofNode> ofxLSExecutor::bookmark(){
    return bookmarks.back();
}

void ofxLSExecutor::addNode(shared_ptr<ofNode> node) {
    branchContainer.push_back(node);
}

void ofxLSExecutor::generate(const string _instruction) {
    reset();
    auto stringInstructions = getInstructionsFromString(_instruction);
    
    for (auto stringInstruction : stringInstructions) {
        auto inst = ofxLSInstruction(stringInstruction);
        auto head = inst.getHead();
        getInstruction(head)(inst.getParams());
    }
    
    //TODO, separate the generation of the node skeleton to mesh construction
    //    float distance;
    //    for(auto b : branchContainer){
    //        if(b->getParent() != nullptr){
    //            cout << "Start"<< endl;
    //            cout << b->getParent()->getGlobalPosition().x;
    //            cout << b->getParent()->getGlobalPosition().y;
    //            cout << b->getParent()->getGlobalPosition().x;
    //            cout << "End" << endl;
    //            cout << b->getGlobalPosition().x;
    //            cout << b->getGlobalPosition().y;
    //            cout << b->getGlobalPosition().x;
    //        }else{
    //            //root point
    //        }
    //
    //    }
    ofxLSExecutor::reset();
}

vector<string> ofxLSExecutor::getInstructionsFromString(string _str){
    // This regex deserves an explanation. Taking a string like:
    // "F[+F-F(1.0,3.2)^F&F\\F/F?|]YU(2.0)A(2.232)?\\/"
    // it returns a vector containing
    //    F
    //    +
    //    F
    //    -
    //    F(1.0,3.2)
    //    ^
    //    F
    //    &
    //    F
    //    \
    //    F
    //    /
    //    F
    //    ?
    //    |
    //    Y
    //    U(2.0)
    //    A(2.232)
    //    ?
    //    \
    //    /
    
    // Explanation:
    // "([A-Z\\^&\\+-\\?\\|/\\]\\[\\\\](\\([0-9\\.,]+\\))*)" this means take any string that start with a capital letter,
    // a ^, a & a +, -, a | a '/', a'\' a'[', a ']'and, if there are, take any number or point '.' enclosed between ()
    return ofxLSUtils::matchesInRegex(_str,"([A-Z\\^&\\+\\-\\?\\|/\\]\\[\\\\](\\([0-9\\.,]+\\))*)");
}
