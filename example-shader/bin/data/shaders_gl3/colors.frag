#version 150
#define SIMPLE_MIX

in vec3 vecNormal;
in vec4 vecPosition;

out vec4 fragColor;

// this are set in the OF app
uniform vec3 uLightPosition;
uniform vec4 uMaterialColor;
uniform float uTime;

void main(){
    // basic lambertian lighting
    vec3 lightDirection = normalize(vecPosition.xyz - uLightPosition);
    float dProd = max(0.0, dot(vecNormal, lightDirection));

    //color
    // the default is the material color
    vec4 color = uMaterialColor;
    #ifdef SIMPLE_MIX
        vec4 colorA = vec4(0.149,0.141,0.912,1.0);
        vec4 colorB = vec4(1.000,0.833,0.224,1.0);
        float pct = abs(sin(uTime));
        color = mix(colorA, colorB, pct);
    #endif


    vec4 col = vec4( vec3( dProd ) * vec3( color ), 1.0 );
    fragColor = col;
}