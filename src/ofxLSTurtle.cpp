#include "ofxLSTurtle.h"

ofxLSTurtle::ofxLSTurtle(float moveLength, float width, float turnAngle, ofxLSGeometryAvailable geometry, bool randomYRotation, bool scaleWidth, int _resolution, int textureRepeat){
    if (validateInput(theta)) {
        theta = turnAngle;
    }

    stepLength = moveLength;
    stepWidth = width;
    resolution = _resolution;
    textureRepeat = textureRepeat;
    geometry = geometry;
    randomYRotation = randomYRotation;
    scaleWidth = scaleWidth;
};

void ofxLSTurtle::setup() {
    //check if axiom, rules and theta are ok,
    // if not, define some default
    
    //clear the sentences
    mesh.clear();
    
    // setup the turtle, the sentences and the geometry
    setMeshMode(geometry);
    reset();

    createInstructions();
};

void ofxLSTurtle::buildSentence(string _sentenceToBuild) {
    mesh.clear();
    executor.generate(_sentenceToBuild);
    createRoot();
    
    historySizes.clear();
    getMesh().clear();
    
    getMesh().append(mesh);
    getMesh().enableNormals();
}

void ofxLSTurtle::createRoot() {
    shared_ptr<ofNode> root(new ofNode);
    root->setPosition(origin);
    executor.addNode(root);
}

void ofxLSTurtle::createInstructions() {
    executor.addInstruction("G", [this](vector<string> params){
        shared_ptr<ofNode> newJoin(new ofNode);
        newJoin->setParent(*executor.back());
        newJoin->boom(params.size() > 0 ? ofToFloat(params[0]) : stepLength);
        executor.addNode(newJoin);
    });
    executor.addInstruction("+", [this](vector<string> params){
        shared_ptr<ofNode> newJoin(new ofNode);
        newJoin->setParent(*executor.back());
        newJoin->roll(params.size() > 0 ? ofToFloat(params[0]) : theta);
        if(randomYRotation){
            newJoin->pan(ofRandom(30.00, 330.00));
        }
        executor.addNode(newJoin);
    });
    executor.addInstruction("-", [this](vector<string> params){
        shared_ptr<ofNode> newJoin(new ofNode);
        newJoin->setParent(*executor.back());
        newJoin->roll(-(params.size() > 0 ? ofToFloat(params[0]) : theta));
        if(randomYRotation){
            newJoin->pan(ofRandom(30.00, 330.00));
        }
        executor.addNode(newJoin);
    });
    executor.addInstruction("|", [this](vector<string> params){
        shared_ptr<ofNode> newJoin(new ofNode);
        newJoin->setParent(*executor.back());
        newJoin->pan(+(params.size() > 0 ? ofToFloat(params[0]) : 180.0));
        executor.addNode(newJoin);
    });
    executor.addInstruction("&", [this](vector<string> params){
        shared_ptr<ofNode> newJoin(new ofNode);
        newJoin->setParent(*executor.back());
        newJoin->tilt(+(params.size() > 0 ? ofToFloat(params[0]) : theta));
        executor.addNode(newJoin);
    });
    executor.addInstruction("^", [this](vector<string> params){
        shared_ptr<ofNode> newJoin(new ofNode);
        newJoin->setParent(*executor.back());
        newJoin->tilt(-(params.size() > 0 ? ofToFloat(params[0]) : theta));
        executor.addNode(newJoin);
    });
    executor.addInstruction("\\", [this](vector<string> params){
        shared_ptr<ofNode> newJoin(new ofNode);
        newJoin->setParent(*executor.back());
        newJoin->pan(+(params.size() > 0 ? ofToFloat(params[0]) : theta));
        executor.addNode(newJoin);
    });
    executor.addInstruction("/", [this](vector<string> params){
        shared_ptr<ofNode> newJoin(new ofNode);
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
        float length = params.size() > 0 ? ofToFloat(params[0]) : stepLength;
        auto beginBranch = executor.back();
        shared_ptr<ofNode> endBranch(new ofNode);
        
        endBranch->setParent(*beginBranch);
        endBranch->move(ofVec3f(0, length, 0));
        
        maybeVectorExpandsBoundingBox(endBranch->getGlobalPosition());
        
        auto widths = getPrevAndCurrentWidth(length);
        auto newBranch = ofxLSBranch(*beginBranch, *endBranch, widths);
        geometryBuilder.putIntoMesh(newBranch, mesh, geometry, resolution, length, textureRepeat);
        executor.addNode(endBranch);
    });
}



void ofxLSTurtle::reset() {
    executor.reset();
    historySizes.clear();
    
    createRoot();
    
    resetBoundingBox();
}



// In case there is the need to keep track of the differents branches width and lenght,
// as in the case when scaleWidth is set to true, this method does 2 things:
// 1) it stores all the sizes in the container historySizes, for each pair, the first value is the length
// the second the width.
// 2) It returns the current width and the previous one, as the method name says.
// If there is no need to keep track of the branch  width, just returns a pair containing
// the default width, both for the prev and current width.
pair<float, float> ofxLSTurtle::getPrevAndCurrentWidth(float currentLength){
    if(!scaleWidth){
        return make_pair(stepWidth, stepWidth);
    }


    float currentWidth = (scaleWidth) ? getScaledWidth(currentLength) : stepWidth;
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
float ofxLSTurtle::getScaledWidth(float currentLength){
    auto ratio = (stepLength / currentLength );
    float currentWidth = stepWidth / ratio;
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
void ofxLSTurtle::maybeVectorExpandsBoundingBox(ofVec3f v){
    if (v.x < boundingBox.min.x) boundingBox.min.x = v.x;
    if (v.y < boundingBox.min.y) boundingBox.min.y = v.y;
    if (v.z < boundingBox.min.z) boundingBox.min.z = v.z;

    if (v.x > boundingBox.max.x) boundingBox.max.x = v.x;
    if (v.y > boundingBox.max.y) boundingBox.max.y = v.y;
    if (v.z > boundingBox.max.z) boundingBox.max.z = v.z;
}

void ofxLSTurtle::computeBoundingBox(){
    for(auto v : mesh.getVertices()){
        if (v.x < boundingBox.min.x) boundingBox.min.x = v.x;
        if (v.y < boundingBox.min.y) boundingBox.min.y = v.y;
        if (v.z < boundingBox.min.z) boundingBox.min.z = v.z;
        
        if (v.x > boundingBox.max.x) boundingBox.max.x = v.x;
        if (v.y > boundingBox.max.y) boundingBox.max.y = v.y;
        if (v.z > boundingBox.max.z) boundingBox.max.z = v.z;
    }
}


void ofxLSTurtle::save(string _filename){
    mesh.save(_filename);
}


void ofxLSTurtle::setMeshMode(ofxLSGeometryAvailable _geometry){
    switch (_geometry) {
        case LINES:
            mesh.setMode(OF_PRIMITIVE_LINES);
            break;
        case TUBES:
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            break;
        case TUBES_DEFORMED:
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            break;
        case TRIANGLES:
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            break;
        default:
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            break;
    }
}

void ofxLSTurtle::resetBoundingBox(){
    boundingBox.min = ofVec3f(0,0,0);
    boundingBox.max = ofVec3f(0,0,0);
}

bool ofxLSTurtle::validateInput(float theta){
    try {
        if(!(theta >= -360.00 && theta <= 360.00)){
            throw ofxLSTurtleError("theta has to be between -360.00 and 360.00");
        }
    } catch (ofxLSTurtleError& e) {
        ofLogError(e.what());
        theta = 25.00;
        return false;
    }
    return true;
}
