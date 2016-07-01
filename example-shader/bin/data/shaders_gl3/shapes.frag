#version 150
in vec3 vecNormal;
in vec4 vecPosition;
in vec2 st;

out vec4 fragColor;

// this are set in the OF app
uniform vec3 uLightPosition;
uniform vec4 uMaterialColor;

void main(){
    // basic lambertian lighting
    vec3 lightDirection = normalize(vecPosition.xyz - uLightPosition);
    float dProd = max(0.0, dot(vecNormal, lightDirection));

    //color
    //vec4 color = uMaterialColor;
    //vec4 col = vec4( vec3( dProd ) * vec3( color ), 1.0 );
    vec4 col = vec4(st, 0.0, 1.0);
    fragColor = col;
}