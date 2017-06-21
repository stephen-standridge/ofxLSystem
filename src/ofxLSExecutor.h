//
//  ofxLSExecutor.hpp
//  example-shader
//
//  Created by kevin ambrosia on 6/20/17.
//
//
#include "ofMain.h"
#include "ofxLSInstruction.h"

class ofxLSExecutor {
typedef const std::function<void(vector<string>)> Lambda;
public:
    void pushNode(shared_ptr<ofNode> const node = NULL);
    void popNode();
    void addNode(shared_ptr<ofNode> const node);
    void reset();
    void generate(const string ruleStr);
    int size() { return branchContainer.size(); };
    
    shared_ptr<ofNode> back();
    shared_ptr<ofNode> bookmark();
    vector<shared_ptr<ofNode> > branchContainer;
    vector<shared_ptr<ofNode> > bookmarks;
    void addInstruction(string identifier, Lambda &lambda){
        instructions.emplace(identifier, lambda);
    };
    Lambda getInstruction(string identifier) {
        return instructions.at(identifier);
    }
    bool hasInstruction(string identifier) {
        return instructions.count(identifier) > 0;
    }
    
private:


    std::map <string, Lambda> instructions;
    vector<string> getInstructionsFromString(string sentence);
};

