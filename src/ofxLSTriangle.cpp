#include "ofxLSTriangle.h"

ofxLSTriangle::ofxLSTriangle(){
    
}

void ofxLSTriangle::generate(ofMesh& mesh, const ofxLSBranch branch){
    const int radius = branch.capSizes.first;
    const int scaledRadius = branch.capSizes.second;
    ofMatrix4x4 beginMatrix = branch.begin.getGlobalTransformMatrix();
    ofMatrix4x4 endMatrix = branch.end.getGlobalTransformMatrix();
    vector<ofVec3f> topValues;
    vector<ofVec3f> bottomValues;

    for (int i = 0; i < resolution; i++){
        float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        float z = ofRandom(0.0, radius);
        ofVec3f circleBottom = ofVec3f(x, y, z);
        bottomValues.push_back(circleBottom);
    }

    for (int i = 0; i < resolution; i++){
        float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
        float x = scaledRadius * cosf(theta);
        float y = scaledRadius * sinf(theta);
        float z = ofRandom(200, 200-scaledRadius);
        ofVec3f circleTop = ofVec3f(x, y, 0.0);
        topValues.push_back(circleTop);
    }


    int n_triangles = resolution;
//    ofVec3f top = branch.end.getGlobalPosition();
//    ofVec3f bottom = branch.begin.getGlobalPosition();
//    float minX = bottom.x -radius;
//    float minY = bottom.y-radius;
//    float maxX = top.x + radius;
//    float maxY = top.y +radius;
//    float maxZ = top.z + radius*2;
//    float minZ = bottom.z;
    int firstIndex = mesh.getNumVertices();
    for (unsigned int i = 0; i< (n_triangles*3); i += 3) {
        int pickTop = ofRandom(0, topValues.size());
        int pickBottom = ofRandom(0, bottomValues.size());
        int pickMiddle = ofRandom(0, bottomValues.size());
        ofVec3f firstV = topValues.at(pickTop);
        ofVec3f thirdV = bottomValues.at(pickBottom);
        ofVec3f secondV = bottomValues.at(pickBottom);
        secondV.z = ofRandom(50, 150);
//        ofVec3f firstV;
//        firstV.x = ofRandom(minX,maxX);
//        firstV.y = ofRandom(minY,maxY);
//        firstV.z = ofRandom(minZ,maxZ);
//        ofVec3f secondV;
//        secondV.x = ofRandom(minX,maxX);
//        secondV.y = ofRandom(minY,maxY);
//        secondV.z = ofRandom(minZ,maxZ);
//        ofVec3f thirdV;
//        thirdV.x = ofRandom(minX,maxX);
//        thirdV.y = ofRandom(minY,maxY);
//        thirdV.z = ofRandom(bottom.z);

        mesh.addIndex(firstIndex +i);
        mesh.addIndex(firstIndex +i+1);
        mesh.addIndex(firstIndex +i+2);

        //find position AND direction of 2 vertices of the triangle;
        ofVec3f e1 = firstV - secondV;
        ofVec3f e2 = thirdV - secondV;
        //Use these 2 vertices to find the normal
        ofVec3f no = e2.cross( e1 ).normalize();

        mesh.addVertex(firstV * endMatrix);
        mesh.addNormal(no);
        mesh.addVertex(secondV * (beginMatrix));
        mesh.addNormal(no);
        mesh.addVertex(thirdV * beginMatrix);
        mesh.addNormal(no);
    }
}
