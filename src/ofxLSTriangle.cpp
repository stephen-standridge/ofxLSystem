#include "ofxLSTriangle.h"

ofxLSTriangle::ofxLSTriangle(){
    
}

void ofxLSTriangle::generate(ofMesh& mesh, const ofxLSBranch branch, const int radius, const int scaledRadius){
    ofMatrix4x4 beginMatrix = branch.begin.getGlobalTransformMatrix();
    ofMatrix4x4 endMatrix = branch.end.getGlobalTransformMatrix();

    int n_triangles = resolution;
    ofVec3f top = branch.end.getGlobalPosition();
    ofVec3f bottom = branch.begin.getGlobalPosition();
    float minX = bottom.x -radius;
    float minY = bottom.y-radius;
    float maxX = top.x + radius;
    float maxY = top.y +radius;
    float maxZ = top.z;
    float minZ = bottom.z;
    int firstIndex = mesh.getNumVertices();
    for (unsigned int i = 0; i< (n_triangles*3); i += 3) {
        ofVec3f firstV;
        firstV.x = ofRandom(minX,maxX);
        firstV.y = ofRandom(minY,maxY);
        firstV.z = ofRandom(minZ,maxZ);
        ofVec3f secondV;
        secondV.x = ofRandom(minX,maxX);
        secondV.y = ofRandom(minY,maxY);
        secondV.z = ofRandom(minZ,maxZ);
        ofVec3f thirdV;
        thirdV.x = ofRandom(minX,maxX);
        thirdV.y = ofRandom(minY,maxY);
        thirdV.z = ofRandom(minZ,maxZ);

        mesh.addIndex(firstIndex +i);
        mesh.addIndex(firstIndex +i+1);
        mesh.addIndex(firstIndex +i+2);

        //find position AND direction of 2 vertices of the triangle;
        ofVec3f e1 = firstV - secondV;
        ofVec3f e2 = thirdV - secondV;
        //Use these 2 vertices to find the normal
        ofVec3f no = e2.cross( e1 ).normalize();

        mesh.addVertex(firstV);
        mesh.addNormal(no);
        mesh.addVertex(secondV);
        mesh.addNormal(no);
        mesh.addVertex(thirdV);
        mesh.addNormal(no);
    }
}
