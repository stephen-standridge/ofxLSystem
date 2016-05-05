#include "ofxLSTriangle.h"

ofxLSTriangle::ofxLSTriangle(){
    
}

void ofxLSTriangle::generate(ofMesh& mesh, const ofxLSBranch branch){
    //if you set offsetBetweenBranches to 0, all the triangles composing
    // the branch will start exactly where the previous one finish,
    // to make them look a bit more intricates, I've overlapped them a bit
    const int offsetBetweenBranches = 20;
    const int radius = branch.capSizes.first;
    const int scaledRadius = branch.capSizes.second;
    ofMatrix4x4 beginMatrix = branch.begin.getGlobalTransformMatrix();
    ofMatrix4x4 endMatrix = branch.end.getGlobalTransformMatrix();
    vector<ofVec3f> topValues;
    vector<ofVec3f> bottomValues;

    // create top and bottom points
    for (int i = 0; i < resolution; i++){
        float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        float y = 0;
        ofVec3f circleBottom = ofVec3f(x, y-offsetBetweenBranches, z);
        bottomValues.push_back(circleBottom);

        float topX = scaledRadius * cosf(theta);
        float topZ = scaledRadius * sinf(theta);
        float topY = 0;
        ofVec3f circleTop = ofVec3f(topX, topY+offsetBetweenBranches, topZ);
        topValues.push_back(circleTop);
    }

    //random shuffle them
    random_shuffle(topValues.begin(), topValues.end());
    random_shuffle(bottomValues.begin(), bottomValues.end());

    int n_triangles = resolution;
    int firstIndex = mesh.getNumVertices();
    for (unsigned int i = 0; i< (n_triangles*3); i += 3) {
        ofVec3f firstV = topValues.at(i/3);
        ofVec3f thirdV = bottomValues.at(i/3);
        ofVec3f secondV = bottomValues.at(i/3);
        secondV.z = ofRandom(-scaledRadius*2, radius*2);
        secondV.y = ofRandom(30, 60);

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
