#include "ofxLSTurtle.h"

template <class GeometryType, class NodeType>
ofxLSTurtle<GeometryType, NodeType>::ofxLSTurtle(float moveLength, float width, float turnAngle, bool randomYRotation, bool scaleWidth, int _resolution, int textureRepeat){
    if (validateInput(theta)) {
        theta = turnAngle;
    }
    mesh.setMode(GeometryType::meshMode);
    stepLength = moveLength;
    stepWidth = width;
    resolution = _resolution;
    textureRepeat = textureRepeat;
    randomYRotation = randomYRotation;
    scaleWidth = scaleWidth;
};

template <class GeometryType, class NodeType>
void ofxLSTurtle<GeometryType, NodeType>::setup() {
    //check if axiom, rules and theta are ok,
    // if not, define some default
    
    //clear the sentences
    mesh.clear();
    
    // setup the turtle, the sentences and the geometry
    
    reset();
    
    createInstructions();
};

template <class GeometryType, class NodeType>
void ofxLSTurtle<GeometryType, NodeType>::buildSentence(string _sentenceToBuild) {
    reset();
    createRoot();
    
    executor.generate(_sentenceToBuild);
    
    historySizes.clear();
    getMesh().clear();
    
    getMesh().append(mesh);
    getMesh().enableNormals();
}

template <class GeometryType, class NodeType>
void ofxLSTurtle<GeometryType, NodeType>::createInstructions() {
    executor.addInstruction("G", [this](vector<string> params){
        shared_ptr<NodeType> newJoin(new NodeType);
        newJoin->setParent(*executor.back());
        newJoin->boom(params.size() > 0 ? ofToFloat(params[0]) : getStepLength());
        executor.addNode(newJoin);
    });
    executor.addInstruction("+", [this](vector<string> params){
        shared_ptr<NodeType> newJoin(new NodeType);
        newJoin->setParent(*executor.back());
        newJoin->roll(params.size() > 0 ? ofToFloat(params[0]) : getTheta());
        if(getRandomYRotation()){
            newJoin->pan(ofRandom(30.00, 330.00));
        }
        executor.addNode(newJoin);
    });
    executor.addInstruction("-", [this](vector<string> params){
        shared_ptr<NodeType> newJoin(new NodeType);
        newJoin->setParent(*executor.back());
        newJoin->roll(-(params.size() > 0 ? ofToFloat(params[0]) : getTheta()));
        if(getRandomYRotation()){
            newJoin->pan(ofRandom(30.00, 330.00));
        }
        executor.addNode(newJoin);
    });
    executor.addInstruction("|", [this](vector<string> params){
        shared_ptr<NodeType> newJoin(new NodeType);
        newJoin->setParent(*executor.back());
        newJoin->pan(+(params.size() > 0 ? ofToFloat(params[0]) : 180.0));
        executor.addNode(newJoin);
    });
    executor.addInstruction("&", [this](vector<string> params){
        shared_ptr<NodeType> newJoin(new NodeType);
        newJoin->setParent(*executor.back());
        newJoin->tilt(+(params.size() > 0 ? ofToFloat(params[0]) : getTheta()));
        executor.addNode(newJoin);
    });
    executor.addInstruction("^", [this](vector<string> params){
        shared_ptr<NodeType> newJoin(new NodeType);
        newJoin->setParent(*executor.back());
        newJoin->tilt(-(params.size() > 0 ? ofToFloat(params[0]) : getTheta()));
        executor.addNode(newJoin);
    });
    executor.addInstruction("\\", [this](vector<string> params){
        shared_ptr<NodeType> newJoin(new NodeType);
        newJoin->setParent(*executor.back());
        newJoin->pan(+(params.size() > 0 ? ofToFloat(params[0]) : getTheta()));
        executor.addNode(newJoin);
    });
    executor.addInstruction("/", [this](vector<string> params){
        shared_ptr<NodeType> newJoin(new NodeType);
        newJoin->setParent(*executor.back());
        newJoin->pan(-(params.size() > 0 ? ofToFloat(params[0]) : 180.0));
        executor.addNode(newJoin);
    });
    executor.addInstruction("[", [this](vector<string> params){
        executor.pushNode();
    });
    executor.addInstruction("]", [this](vector<string> params){
        executor.addNode(executor.bookmark());
        executor.popNode();
    });
    executor.addInstruction("F", [this](vector<string> params){
        float length = params.size() > 1 ? ofToFloat(params[1]) : getStepLength();
        float shouldDraw = params.size() > 0 && params[0] == "1" ? false : true;
        auto beginBranch = executor.back();
        shared_ptr<NodeType> endBranch(new NodeType);
        
        endBranch->setParent(*beginBranch);
        endBranch->move(ofVec3f(0, length, 0));
        
        maybeVectorExpandsBoundingBox(endBranch->getGlobalPosition());
        
        auto widths = getPrevAndCurrentWidth(length);
        
        auto newBranch = ofxLSBranch(*beginBranch, *endBranch, widths);
        geometryBuilder.putIntoMesh(newBranch, mesh, getResolution(), getStepLength(), getTextureRepeat());
        executor.addNode(endBranch);
    });
}


template <class GeometryType, class NodeType>
void ofxLSTurtle<GeometryType, NodeType>::reset() {
    executor.reset();
    historySizes.clear();
    mesh.clear();
    resetBoundingBox();
}


// In case there is the need to keep track of the differents branches width and lenght,
// as in the case when scaleWidth is set to true, this method does 2 things:
// 1) it stores all the sizes in the container historySizes, for each pair, the first value is the length
// the second the width.
// 2) It returns the current width and the previous one, as the method name says.
// If there is no need to keep track of the branch  width, just returns a pair containing
// the default width, both for the prev and current width.
template <class GeometryType, class NodeType>
pair<float, float> ofxLSTurtle<GeometryType, NodeType>::getPrevAndCurrentWidth(float currentLength){
    if(!scaleWidth){
        return make_pair(getStepWidth(), getStepWidth());
    }
    
    
    float currentWidth = (getScaleWidth()) ? getScaledWidth(currentLength) : getStepWidth();
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

//it scales the with proportionally to the scaled length
//
template <class GeometryType, class NodeType>
float ofxLSTurtle<GeometryType, NodeType>::getScaledWidth(float currentLength){
    auto ratio = (getStepLength() / currentLength );
    float currentWidth = getStepWidth() / ratio;
    return currentWidth;
    if (currentWidth < 0.2) {
        return 0.2;
    } else {
        return currentWidth;
    }
}

// keep in mind that this method does not consider the thikness of a branch, but just the position of the vertices
// that will be used later to generate the cylinder. Therefore, it is not accurate, but is is usefull to get the UV
// if you want higher precision, call ofxLSystem.computeBoundingBox(), that iterates on all the vertices composing the
// mesh
template <class GeometryType, class NodeType>
void ofxLSTurtle<GeometryType, NodeType>::maybeVectorExpandsBoundingBox(ofVec3f v){
    if (v.x < boundingBox.min.x) boundingBox.min.x = v.x;
    if (v.y < boundingBox.min.y) boundingBox.min.y = v.y;
    if (v.z < boundingBox.min.z) boundingBox.min.z = v.z;
    
    if (v.x > boundingBox.max.x) boundingBox.max.x = v.x;
    if (v.y > boundingBox.max.y) boundingBox.max.y = v.y;
    if (v.z > boundingBox.max.z) boundingBox.max.z = v.z;
}

template <class GeometryType, class NodeType>
void ofxLSTurtle<GeometryType, NodeType>::computeBoundingBox(){
    for(auto v : mesh.getVertices()){
        if (v.x < boundingBox.min.x) boundingBox.min.x = v.x;
        if (v.y < boundingBox.min.y) boundingBox.min.y = v.y;
        if (v.z < boundingBox.min.z) boundingBox.min.z = v.z;
        
        if (v.x > boundingBox.max.x) boundingBox.max.x = v.x;
        if (v.y > boundingBox.max.y) boundingBox.max.y = v.y;
        if (v.z > boundingBox.max.z) boundingBox.max.z = v.z;
    }
}

template <class GeometryType, class NodeType>
void ofxLSTurtle<GeometryType, NodeType>::save(string _filename){
    mesh.save(_filename);
}

template <class GeometryType, class NodeType>
void ofxLSTurtle<GeometryType, NodeType>::resetBoundingBox(){
    boundingBox.min = ofVec3f(0,0,0);
    boundingBox.max = ofVec3f(0,0,0);
}

template <class GeometryType, class NodeType>
bool ofxLSTurtle<GeometryType, NodeType>::validateInput(float _theta){
    try {
        if(!(_theta >= -360.00 && _theta <= 360.00)){
            throw ofxLSTurtleError("theta has to be between -360.00 and 360.00");
        }
    } catch (ofxLSTurtleError& e) {
        ofLogError(e.what());
        theta = 25.00;
        return false;
    }
    return true;
}
