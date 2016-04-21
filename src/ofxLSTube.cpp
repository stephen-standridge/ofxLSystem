#include "ofxLSTube.h"

ofxLSTube::ofxLSTube(){
    
}

void ofxLSTube::generate(ofMesh& mesh, const ofxLSBranch branch, const int radius, const int scaledRadius){
    ofMatrix4x4 beginMatrix = branch.begin.getGlobalTransformMatrix();
    ofMatrix4x4 endMatrix = branch.end.getGlobalTransformMatrix();

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
        float y = radius * sinf(theta);
        ofVec3f circleBottom = ofVec3f(x, y, 0.0);
        ofVec3f direction = (ofVec3f() + circleBottom).getNormalized();

        float xTop = scaledRadius * cosf(theta);
        float yTop = scaledRadius * sinf(theta);
        ofVec3f circleTop = ofVec3f(xTop, yTop, 0.0);

        // bottom
        mesh.addVertex(circleBottom * beginMatrix);
        mesh.addNormal(direction * beginMatrix.getRotate());
        //top
        mesh.addVertex(circleTop * endMatrix);
        mesh.addNormal(direction * endMatrix.getRotate());
    }

    //cap on the top
    // As that one on the bottom is normally not visible, we skip it
    // Please note: the cap is done adding only one vertex in the middle of
    // the cylinder in the top part, and using the indexes to connect the
    // top vertexes that make the body of the cylinder with this middle point.
    // Therefore, the normal are not correct, because the top vertices of
    // the cilynder body are looking perpendicular to the faces of the cylinder
    // as they should. To have correct normals, I should add another circle on the top
    // (the code is that one above, commented), but that would have meant to add N resolution vertices for each tube.
    // As the imperfection is difficult to see, i prefer to have wrong normals but less vertices. I do not exclude that this would change in the future

    int topMiddlePoint = mesh.getNumVertices();
    ofVec3f topDir =branch.end.getPosition().getNormalized();
    mesh.addVertex(branch.end.getGlobalPosition()); //exp
    mesh.addNormal(topDir * endMatrix.getRotate()); //exp
    if(semplifiedCap){
        for (int i = 0; i < resolution; i++){
            if (i == (resolution-1)) {
                //closing triangle
                mesh.addIndex(topMiddlePoint);
                mesh.addIndex(first+ (2*i + 1));
                mesh.addIndex(first+1);
            } else {
                //indices
                mesh.addIndex(topMiddlePoint);
                mesh.addIndex(first+ (2*i + 1));
                mesh.addIndex(first+ (2*i + 1) + 2);
            }
        }
    }else{
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
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            ofVec3f circleTemp = ofVec3f(x, y, 0.0);
            ofVec3f topDir = branch.end.getPosition().getNormalized();
            mesh.addVertex(circleTemp * branch.end.getGlobalTransformMatrix());
            mesh.addNormal(topDir * endMatrix.getRotate());
        }

    }
}
