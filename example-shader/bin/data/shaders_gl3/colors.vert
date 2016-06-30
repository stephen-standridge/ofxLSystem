#version 150
out vec3 vecNormal;
out vec3 vecPosition;


in vec4 position;
in vec4 color;
in vec4 normal;

// these are passed in from OF programmable renderer
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 normalMatrix;

// this are set in the OF app
uniform float uTime;

void main(){
    // Since the light is in world coordinates, i need the vertex position in world
    // coordinates too.
    vecPosition = (modelViewMatrix * position).xyz;

    vecNormal = normal.xzy;
    gl_Position = modelViewProjectionMatrix * position;
}