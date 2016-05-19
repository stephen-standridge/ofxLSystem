#include "ofxLSTube.h"

ofxLSTube::ofxLSTube(){
    
}

void ofxLSTube::generate(ofMesh& mesh, const ofxLSBranch branch){
    bool cap = true;
    const int radius = branch.capSizes.first;
    const int scaledRadius = branch.capSizes.second;
    ofMatrix4x4 beginMatrix = branch.begin.getGlobalTransformMatrix();
    ofMatrix4x4 endMatrix = branch.end.getGlobalTransformMatrix();

    // Cylinder body
    int first = mesh.getNumVertices();
    for (int i = 0; i < resolution; i++){
        // if it is the last face, close it where the first face
        // was started
        if(i == resolution -1){
            mesh.addIndex(first+(i*2));
            mesh.addIndex(first);
            mesh.addIndex(first+1);

            mesh.addIndex(first+1);
            mesh.addIndex(first+(i*2)+1);
            mesh.addIndex(first+(i*2));
        }else{
            mesh.addIndex(first+(i*2));
            mesh.addIndex(first+(i*2)+2);
            mesh.addIndex(first+(i*2)+3);

            mesh.addIndex(first+(i*2)+3);
            mesh.addIndex(first+(i*2)+1);
            mesh.addIndex(first+(i*2));
        }
    }
    
    for (int i = 0; i < resolution; i++){
        //calculate x and y component
        float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        ofVec3f circleBottom = ofVec3f(x, 0.0, z);
        ofVec3f direction = (ofVec3f() + circleBottom).getNormalized();

        float xTop = scaledRadius * cosf(theta);
        float zTop = scaledRadius * sinf(theta);
        ofVec3f circleTop = ofVec3f(xTop, 0.0, zTop);
        ofVec2f tcoord;

        // bottom
        mesh.addVertex(circleBottom * beginMatrix);
        mesh.addNormal(direction * beginMatrix.getRotate());
        //top
        mesh.addVertex(circleTop * endMatrix);
        mesh.addNormal(direction * endMatrix.getRotate());
    }

    // Cylinder cap
    if (cap) {
        int topMiddlePoint = mesh.getNumVertices();
        ofVec3f topDir = branch.end.getPosition().getNormalized();
        mesh.addVertex(branch.end.getGlobalPosition());
        mesh.addNormal(topDir * endMatrix.getRotate());

        for (int i = 0; i < resolution; i++){
            if (i == (resolution-1)) {
                //closing triangle
                mesh.addIndex(topMiddlePoint);
                mesh.addIndex(topMiddlePoint+ i + 1);
                mesh.addIndex(topMiddlePoint+1);
            } else {
                //indices
                mesh.addIndex(topMiddlePoint);
                mesh.addIndex(topMiddlePoint+ i + 1);
                mesh.addIndex(topMiddlePoint+ i + 2);
            }
            //add vertex
            float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
            float x = scaledRadius * cosf(theta);
            float z = scaledRadius * sinf(theta);

            ofVec3f circleTemp = ofVec3f(x, 0.0, z);
            mesh.addVertex(circleTemp * branch.end.getGlobalTransformMatrix());
            mesh.addNormal(topDir * endMatrix.getRotate());
        }
    }
}
