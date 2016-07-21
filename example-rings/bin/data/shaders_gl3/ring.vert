#version 150
//https://thebookofshaders.com/07/

out vec3 vecNormal;
out vec4 vecPosition;
out vec2 st;

in vec4 position;
in vec4 normal;

// these are passed in from OF programmable renderer
uniform mat4 modelViewProjectionMatrix;
uniform vec2 uTreeResolution;
uniform vec2 uMinTree;
uniform vec2 uMaxTree;
uniform float uScale;


float map(float x, float in_min, float in_max, float out_min, float out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void main(){
    // Since the light is in world coordinates, i need the vertex position in world
    // coordinates too.
    //vec4 newPosition = position + normal * uScale;
    //vecPosition = modelViewProjectionMatrix * newPosition;
    vecPosition = modelViewProjectionMatrix * position;
    float x = map(position.x,uMinTree.x, uMaxTree.x, 0, uTreeResolution.x);
    float y = map(position.y,uMinTree.y, uMaxTree.y, 0, uTreeResolution.y);
    // this variable st is like gl_FragCoord.xy/screenResolution, but it
    // consider each pixel relative to the bounding box of the mesh instead that the
    // dimension of the screen. This calculation screw up as soon as we move the mesh
    // because we should recalculate the bounding box too.
    st = vec2(x/uTreeResolution.x, y/uTreeResolution.y);
    vecNormal = normal.xzy;
    gl_Position = vecPosition;
}