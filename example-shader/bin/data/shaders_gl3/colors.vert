#version 150

in vec4 position;
uniform mat4 modelViewProjectionMatrix;

uniform float uTime;

void main(){

    //get our current vertex position so we can modify it
    vec4 pos = modelViewProjectionMatrix * position;

    //finally set the pos to be that actual position rendered
    gl_Position = pos;
}