#version 150

out vec4 fragColor;
uniform float uTime;

void main(){
    vec4 colorA = vec4(0.149,0.141,0.912,1.0);
    vec4 colorB = vec4(1.000,0.833,0.224,1.0);
    float pct = sin(uTime);
    fragColor = mix(colorA, colorB, pct);

}