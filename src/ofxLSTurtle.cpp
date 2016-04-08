#include "ofxLSTurtle.h"

void ofxLSTurtle::setup( float _moveLength, float _width, float _turnAngle, ofxLSGeometryAvailable _geometry, bool _randomZRotation, bool _scaleWidth) {
    defaultLength = _moveLength;
    width = _width;
    theta = _turnAngle;
    geometry = _geometry;
    randomZRotation = _randomZRotation;
    scaleWidth = _scaleWidth;
    bookmarks.clear();
    branchContainer.clear();
    historySizes.clear();
    shared_ptr<ofNode> root(new ofNode);
    root->setPosition(origin);
    branchContainer.push_back(root);
}

void ofxLSTurtle::generate(ofVboMesh& mesh, const string _instruction, const int _depth) {
    bool branching = false;
    auto instructions = getInstructionsFromString(_instruction);

    for (auto stringInstruction : instructions) {
        auto inst = ofxLSInstruction(stringInstruction);
        auto head = inst.getHead();
        if (head == "F") {
            branching =  true;
        }else if( head == "G") {
            shared_ptr<ofNode> newJoin(new ofNode);
            newJoin->setParent(*branchContainer.back());
            newJoin->dolly(inst.getLength(defaultLength));
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
            float length = inst.getLength(defaultLength);

            auto beginBranch = branchContainer.back();
            shared_ptr<ofNode> endBranch(new ofNode);
            endBranch->setParent(*branchContainer.back());
            endBranch->move(ofVec3f(0, 0, length));
            auto newBranch = ofxLSBranch(*beginBranch, *endBranch);
            auto widths = getPrevAndCurrentWidth(length);
            geometryBuilder.putIntoMesh(newBranch, mesh, widths.first, widths.second, geometry);
            branchContainer.push_back(endBranch);
            branching = false;
        }
    }
    branchContainer.clear();
    bookmarks.clear();
}

// This method not only return the previous and current width, but it keeps track
// of all the the change in size that the tree has experienced.
// The first value is the length, the second the width.

pair<float, float> ofxLSTurtle::getPrevAndCurrentWidth(float currentLength){
    float currentWidth = (scaleWidth) ? getScaledWidth(currentLength) : width;
    if (historySizes.empty()) {
        historySizes.insert(make_pair(currentLength, currentWidth));
        return (make_pair(currentWidth, currentWidth));
    } else {
        map<float, float>::iterator current;
        if (historySizes.find(currentLength) == historySizes.end()) {
            historySizes.insert(make_pair(currentLength, currentWidth));
            current = historySizes.begin();
        } else {
            current = historySizes.find(currentLength);
        }
        auto prev = current;
        ++prev;
        return make_pair(prev->second, current->second);
    }
}

float ofxLSTurtle::getScaledWidth(float currentLength){
    auto ratio = defaultLength / currentLength;
    float currentWidth = width / ratio;
    if (currentWidth < 1) {
        return 1;
    } else {
        return currentWidth;
    }
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
