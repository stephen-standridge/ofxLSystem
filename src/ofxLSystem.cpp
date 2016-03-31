#include "ofxLSystem.h"
void ofxLSystem::setup(
    string _axiom,
    vector<string> _strRules,
    int _depth,
    float _theta,
    float _stepWidth,
    float _stepLength,
    ofVec3f _position,
    map<string, float> _constants,
    bool _randomZRotation,
    ofxLSGeometryAvailable _geometry){

    try {
        validateInput(_axiom, _strRules, theta);
        this->setGlobalPosition(_position);
        axiom = _axiom;
        rulesContainer = _strRules;
        depth = _depth;
        constants = _constants;
        turtle.setup(_stepLength, _stepWidth, _theta, _geometry, _position, _randomZRotation);
        mesh.clear();
        setMeshMode(_geometry);
    } catch (ofxLSInputError& e) {
        ofLogError(e.what());
        // do not brake the program, initialize some standard variables
        // and return an error message. This behaviour is suggested in the OF dev styleguide
        axiom = "F";
        rulesContainer = vector<string>{"F -> FF"};
        depth = 1;
        constants = Constants();
        turtle.setup(_stepLength, _stepWidth, 25.00, TUBES, ofVec3f(100,100,0), false);
        mesh.clear();
        setMeshMode(_geometry);
    }
}

//begin method overloading of setup:
void ofxLSystem::setup(
                    string _axiom,
                    vector<string> _strRules,
                    int _depth,
                    float _theta,
                    ofVec3f _position,
                    map<string, float> _constants,
                    bool _randomZRotation,
                    ofxLSGeometryAvailable _geometry){
    setup(_axiom, _strRules, _depth, _theta, stepWidth, stepLength, _position, _constants, _randomZRotation, _geometry);
}

void ofxLSystem::setup(
                       string _axiom,
                       vector<string> _strRules,
                       int _depth,
                       float _theta,
                       float _stepWidth,
                       float _stepLength,
                       ofVec3f _position){
    map<string, float> _constants = Constants();
    setup(_axiom, _strRules, _depth, _theta, _stepWidth, _stepLength, _position, _constants, true, TUBES);
}



void ofxLSystem::build(){
    const vector<string> sentences = ofxLSystemGrammar::buildSentences(rulesContainer, depth, axiom, constants);
    normalsMesh.clear();
    mesh.clear();
    turtle.generate(mesh, sentences.back(), depth);

    // this part is needed by of3DPrimitive
    getMesh() = mesh;
    //getMesh().enableNormals(); it does not work
    normalizeAndApplySavedTexCoords();
}

void ofxLSystem::setMeshMode(ofxLSGeometryAvailable _geometry){
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
        default:
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            break;
    }
}

//this code is copy&pastef from of3DPrimitive
void ofxLSystem::drawNormals(float length, bool bFaceNormals) const{
    const vector<ofVec3f>& normals    = mesh.getNormals();
    const vector<ofVec3f>& vertices   = mesh.getVertices();
    ofVec3f normal;
    ofVec3f vert;

    normalsMesh.setMode( OF_PRIMITIVE_LINES );
    normalsMesh.getVertices().resize( normals.size() * 2);

    if (bFaceNormals) {
        for(int i = 0; i < (int)normals.size(); i++ ) {
            if(i % 3 == 0) {
                vert = (vertices[i]+vertices[i+1]+vertices[i+2]) / 3;
            } else if (i % 3 == 1) {
                vert = (vertices[i-1]+vertices[i]+vertices[i+1]) / 3;
            } else if ( i % 3 == 2) {
                vert = (vertices[i-2]+vertices[i-1]+vertices[i]) / 3;
            }
            normalsMesh.setVertex(i*2, vert);
            normal = normals[i].getNormalized();
            normal *= length;
            normalsMesh.setVertex(i*2+1, normal+vert);
        }
    } else {
        for(int i = 0; i < (int)normals.size(); i++) {
            vert = vertices[i];
            normal = normals[i].getNormalized();
            normalsMesh.setVertex( i*2, vert);
            normal *= length;
            normalsMesh.setVertex(i*2+1, normal+vert);
        }
    }
    normalsMesh.draw();
}

bool ofxLSystem::isAxiomInRules(string _axiom, vector<string> _rulesContainer){
    auto lettersInAxiom = ofxLSUtils::matchesInRegex(_axiom, "[a-zA-Z]");
    for(auto letter : lettersInAxiom){
        for(string rule : _rulesContainer){
            if(ofxLSUtils::countSubstring(rule, letter) > 0){
                return true;
            }
        }
    }

    return false;
}

bool ofxLSystem::thetaValueIsinRange(float theta){
    return (theta >= -360.00 && theta <= 360.00) ? true : false;
}

void ofxLSystem::validateInput(string _axiom, vector<string> _strRules, float theta){
    if(!isAxiomInRules(_axiom, _strRules)){
        throw ofxLSInputError("axiom is not in rules container");
    }
    if(!thetaValueIsinRange(theta)){
        throw ofxLSInputError("theta has to be between -360.00 and 360.00");
    }
}