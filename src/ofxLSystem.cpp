#include "ofxLSystem.h"

void ofxLSystem::setup(
                    int _depth,
                    string _axiom,
                    float _theta,
                    string _strRules,
                    ofVec3f _position,
                    map<string, float> _constants,
                    bool _randomYRotation,
                    string _geometry){
    axiom = _axiom;
    ruleString = _strRules;
    depth = _depth;
    constants = _constants;
    turtle.setup(100.0, 10, _theta, _geometry, _position, _randomYRotation);
    mesh.clear();
    setMeshMode(_geometry);
}

void ofxLSystem::draw(){
    mesh.draw();
}

void ofxLSystem::drawWireframe(){
    mesh.drawWireframe();
}

void ofxLSystem::drawFaces(){
    mesh.drawFaces();
}

void ofxLSystem::build(){
    const vector<string> sentences = ofxLSystemGrammar::buildSentences(ruleString, depth, axiom, constants);
    normalsMesh.clear();
    mesh.clear();
//    for(auto sentence : sentences){
//        turtle.generate(mesh, sentence, depth);
//    }

    turtle.generate(mesh, sentences.back(), depth);
}

void ofxLSystem::setMeshMode(string _geometry){
    if(_geometry == "line"){
        mesh.setMode(OF_PRIMITIVE_LINES);
    }else if(_geometry == "tube"){
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    }else {
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    }
}

// this code is copy&pastef from of3DPrimitive
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
