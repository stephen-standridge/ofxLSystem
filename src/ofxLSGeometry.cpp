#include "ofxLSGeometry.h"

void ofxLSGeometry::putIntoMesh(const ofxLSBranch branch, ofVboMesh& mesh, const float width, const float scaledWidth, ofxLSGeometryAvailable _geometryType, int resolution){
    //Branch deve contenere solo 2 ofNode, uno per l'inizio del segmento e
    // uno per la fine. Tutto il resto viene implementato dalla geometria
    switch (_geometryType) {
        case TUBES:
            tube.generate(mesh, branch, width, scaledWidth);
            break;
        case TUBES_DEFORMED:
            tubeDeformed.generate(mesh, branch, width);
            break;
        case LINES:
            tubeDeformed.generate(mesh, branch, width);
            break;
        case TRIANGLES:
            triangle.generate(mesh, branch, width, scaledWidth);
            break;
        default:
            line.generate(mesh, branch, width);
            break;
    }
}
