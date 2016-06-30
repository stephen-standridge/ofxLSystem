#version 150
in vec3 vecNormal;
in vec3 vecPosition;

out vec4 fragColor;

// these are passed in from OF programmable renderer
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 normalMatrix;
// this are set in the OF app
uniform float uTime;
uniform vec4 uLightColor;
uniform vec3 uLightPosition;
uniform vec4 uMaterialColor;

void main(){
    vec3 lightDirection = normalize(vecPosition - uLightPosition);
//    vec4 colorA = vec4(0.149,0.141,0.912,1.0);
//    vec4 colorB = vec4(1.000,0.833,0.224,1.0);
//    float pct = sin(uTime);
//    vec4 color = mix(colorA, colorB, pct);

    vec3 light = vec3(0.5, 0.2, 1.0);
    light = normalize(light);

    //bn
    float dProd = max(0.0,
                       dot(vecNormal, lightDirection));
    fragColor = vec4(dProd, dProd, dProd, 1);

    //color
    //vec4 color = vec4(1.0,0.0,0.0,1);
    vec4 color = uMaterialColor;

    vec4 col = vec4( vec3( dProd ) * vec3( color ), 1.0 );
    fragColor = col;
}