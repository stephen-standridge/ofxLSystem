#include "ofxLSGeometry.h"

void ofxLSGeometry::putIntoMesh(const ofxLSBranch branch, ofVboMesh& mesh, const float width, ofxLSGeometryAvailable _geometryType){
    //Branch deve contenere solo 2 ofNode, uno per l'inizio del segmento e
    // uno per la fine. Tutto il resto viene implementato dalla geometria
    switch (_geometryType) {
        case TUBES:
            tube.generate(mesh, branch, width);
            break;
        case TUBES_DEFORMED:
            tubeDeformed.generate(mesh, branch, width);
            break;
        case LINES:
            tubeDeformed.generate(mesh, branch, width);
            break;
        default:
            line.generate(mesh, branch, width);
            break;
    }
}
