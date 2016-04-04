#include "ofxLSTurtle.h"

void ofxLSTurtle::setup( float _moveLength, float _width, float _turnAngle, ofxLSGeometryAvailable _geometry, bool _randomZRotation) {
    defaultLength = _moveLength;
    width = _width;
    theta = _turnAngle;
    geometry = _geometry;
    randomZRotation = _randomZRotation;
    bookmarks.clear();
    branchContainer.clear();
    shared_ptr<ofNode> root(new ofNode);
    root->setPosition(origin);
    branchContainer.push_back(root);
}

void ofxLSTurtle::generate(ofVboMesh& mesh, const string _instruction, const int _depth) {
    bool branching = false;
    int currentLength = defaultLength;
    auto instructions = getInstructionsFromString(_instruction);

    for (auto stringInstruction : instructions) {
        auto inst = ofxLSInstruction(stringInstruction);
        auto head = inst.getHead();
        if (head == "F") {
            branching =  true;
        }else if( head == "G") {
            shared_ptr<ofNode> newJoin(new ofNode);
            newJoin->setParent(*branchContainer.back());
            newJoin->dolly(inst.getLength(currentLength));
            branchContainer.push_back(newJoin);
        }else if (head == "+") {
            shared_ptr<ofNode> newJoin(new ofNode);
            newJoin->setParent(*branchContainer.back());
            newJoin->pan(+inst.getAngle(theta));
            if(randomZRotation){
                newJoin->roll(ofRandom(30.00, 330.00));
            }
            branchContainer.push_back(newJoin);
        }else if (head == "-") {
            shared_ptr<ofNode> newJoin(new ofNode);
            newJoin->setParent(*branchContainer.back());
            newJoin->pan(-inst.getAngle(theta));
            if(randomZRotation){
                newJoin->roll(ofRandom(30.00, 330.00));
            }
            branchContainer.push_back(newJoin);
        }else if (head == "|") {
            shared_ptr<ofNode> newJoin(new ofNode);
            newJoin->setParent(*branchContainer.back());
            newJoin->roll(+inst.getAngle(180.00));
            branchContainer.push_back(newJoin);
        }else if (head == "&") {
            shared_ptr<ofNode> newJoin(new ofNode);
            newJoin->setParent(*branchContainer.back());
            newJoin->tilt(+inst.getAngle(theta));
            branchContainer.push_back(newJoin);
        }
        else if (head == "^") {
            shared_ptr<ofNode> newJoin(new ofNode);
            newJoin->setParent(*branchContainer.back());
            newJoin->tilt(-inst.getAngle(theta));
            branchContainer.push_back(newJoin);
        }
        else if (head == "\\") {
            shared_ptr<ofNode> newJoin(new ofNode);
            newJoin->setParent(*branchContainer.back());
            newJoin->roll(+inst.getAngle(theta));
            branchContainer.push_back(newJoin);
        }
        else if (head == "/") {
            shared_ptr<ofNode> newJoin(new ofNode);
            newJoin->setParent(*branchContainer.back());
            newJoin->roll(-inst.getAngle(180.00));
            branchContainer.push_back(newJoin);
        }
        else if (head == "[") {
            bookmarks.push_back(branchContainer.back());
        }
        else if (head == "]") {
            branchContainer.push_back(bookmarks.back());
            bookmarks.pop_back();
        }

        if (branching) {
            auto beginBranch = branchContainer.back();
            shared_ptr<ofNode> endBranch(new ofNode);
            endBranch->setParent(*branchContainer.back());
            endBranch->move(ofVec3f(0, 0, inst.getLength(currentLength)));
            auto newBranch = ofxLSBranch(*beginBranch, *endBranch);
            geometryBuilder.putIntoMesh(newBranch, mesh, width, geometry);
            branchContainer.push_back(endBranch);
            branching = false;
        }
    }
    branchContainer.clear();
    bookmarks.clear();
}

vector<string> ofxLSTurtle::getInstructionsFromString(string _str){
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
