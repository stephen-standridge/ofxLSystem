//
//  ofxLSExecutor.hpp
//  example-shader
//
//  Created by kevin ambrosia on 6/20/17.
//
//
#pragma once;
#include "ofMain.h"
#include "ofxLSInstruction.h"

template <class Node>

class ofxLSExecutor {
typedef const std::function<void(vector<string>)> Lambda;
public:
    void popNode()          { bookmarks.pop_back(); };
    void pushNode(shared_ptr<Node> const node = NULL) {
        if(node != NULL) {
            bookmarks.push_back(node);
        } else {
            bookmarks.push_back(branchContainer.back());
        }
    }
    void reset() {
        bookmarks.clear();
        branchContainer.clear();
    }
    void addNode(shared_ptr<Node> const node) { branchContainer.push_back(node); }
    int size()                      { return branchContainer.size(); };
    shared_ptr<Node> back()         { return branchContainer.back(); };
    shared_ptr<Node> bookmark()     { return bookmarks.back(); };

    void addInstruction(string identifier, Lambda &lambda){
        instructions.emplace(identifier, lambda);
    };
    Lambda getInstruction(string identifier) {
        return instructions.at(identifier);
    }
    bool hasInstruction(string identifier) {
        return instructions.count(identifier) > 0;
    }
    
    void generate(const string _instruction) {
        bookmarks.clear();
        auto stringInstructions = getInstructionsFromString(_instruction);
        
        for (auto stringInstruction : stringInstructions) {
            auto inst = ofxLSInstruction(stringInstruction);
            auto head = inst.getHead();
            if (hasInstruction(head)){
                getInstruction(head)(inst.getParams());
            }
        }
        reset();
    }
    
    vector<string> getInstructionsFromString(string _str) { return ofxLSUtils::matchesInRegex(_str, parametricMatching); };
    
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
    string parametricMatching = "([A-Z\\^&\\+\\-\\?\\|/\\]\\[\\\\](\\([0-9\\.,]+\\))*)";

private:
    vector<shared_ptr<Node> > branchContainer;
    vector<shared_ptr<Node> > bookmarks;
    std::map <string, Lambda> instructions;
};

