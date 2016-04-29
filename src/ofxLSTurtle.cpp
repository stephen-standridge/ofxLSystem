#include "ofxLSTurtle.h"

void ofxLSTurtle::setup( float _moveLength, float _width, float _turnAngle, ofxLSGeometryAvailable _geometry, bool _randomZRotation, bool _scaleWidth, int _resolution) {
    defaultLength = _moveLength;
    width = _width;
    theta = _turnAngle;
    resolution = _resolution;
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
            auto widths = getPrevAndCurrentWidth(length);
            auto newBranch = ofxLSBranch(*beginBranch, *endBranch, widths);
            geometryBuilder.putIntoMesh(newBranch, mesh, widths.first, widths.second, geometry, resolution);
            branchContainer.push_back(endBranch);
            branching = false;
        }
    }

// TODO, separate the generation of
//    for(auto b : branchContainer){
//
//    }
    branchContainer.clear();
    bookmarks.clear();
    historySizes.clear();
}

// In case there is the need to keep track of the differents branches width and lenght,
// as in the case when scaleWidth is set to true, this method does 2 things:
// 1) it stores all the sizes in the container historySizes, for each pair, the first calue is the lenght
// the second the width.
// 2) It returns the current width and the previous one, as the method name says.
// If there is no need to keep track of the branch  width, just returns a pair containing
// the default width, both for the prev and current width.
pair<float, float> ofxLSTurtle::getPrevAndCurrentWidth(float currentLength){
    if(!scaleWidth){
        return make_pair(width, width);
    }


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
