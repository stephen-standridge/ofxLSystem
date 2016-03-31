#include "ofxLSLine.h"

ofxLSLine::ofxLSLine(){
    
}

void ofxLSLine::generate(ofMesh& mesh, ofxLSBranch branch, int radius){
    auto start = branch.begin.getGlobalPosition();
    auto end = branch.end.getGlobalPosition();
    auto numberCurrentVertices = mesh.getNumVertices();
    
    mesh.addVertex(start);
    mesh.addNormal(start.getNormalized());
    
    mesh.addVertex(end);
    mesh.addNormal(end.getNormalized());
    
    mesh.addIndex(numberCurrentVertices);
    mesh.addIndex(numberCurrentVertices+1);
}
