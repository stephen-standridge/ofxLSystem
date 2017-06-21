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
