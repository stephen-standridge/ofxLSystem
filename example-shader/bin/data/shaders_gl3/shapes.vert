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

void main(){
    // Since the light is in world coordinates, i need the vertex position in world
    // coordinates too.
    vecPosition = modelViewProjectionMatrix * position;
    st = vec2(position.x/uTreeResolution.x, position.y/uTreeResolution.y);

    vecNormal = normal.xzy;
    gl_Position = vecPosition;
}