#version 150
// https://thebookofshaders.com/06/

out vec3 vecNormal;
out vec4 vecPosition;

in vec4 position;
in vec4 normal;

// these are passed in from OF programmable renderer
uniform mat4 modelViewProjectionMatrix;
uniform float treeMinHeight;
uniform float treeMaxHeight;

void main(){
    // Since the light is in world coordinates, i need the vertex position in world
    // coordinates too.
    vecPosition = modelViewProjectionMatrix * position;

    vecNormal = normal.xzy;
    gl_Position = vecPosition;
}