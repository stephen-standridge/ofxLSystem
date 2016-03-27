#include "ofxLSGeometry.h"

void ofxLSGeometry::putIntoMesh(const ofxLSBranch branch, ofVboMesh& mesh, const float width, const string _geometryType){
    //Branch deve contenere solo 2 ofNode, uno per l'inizio del segmento e
    // uno per la fine. Tutto il resto viene implementato dalla geometria
    if(_geometryType == "tube"){
        tube.generate(mesh, branch, width);
    }else if(_geometryType == "line"){
        line.generate(mesh, branch, width);
    }else if(_geometryType == "tube_deformed"){
        tubeDeformed.generate(mesh, branch, width);
    }else{
        ofLogError("NO GEOMETRY AVAILABLE FOR GEOMETRY TYPE: ");
    }
}
