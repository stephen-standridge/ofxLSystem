#version 150

in vec3 vecNormal;
in vec4 vecPosition;
in vec2 st;

out vec4 fragColor;

// these are set in the OF app
uniform vec3 uLightPosition;
uniform vec4 uMaterialColor;
uniform float uTime;
//these are custom uniforms
uniform float uThickness;
uniform float uScale;
uniform float uThreshold;
uniform float uNRing;
uniform vec4 uRingColor;
uniform int uUseLight;

// http://www.iquilezles.org/www/articles/functions/functions.htm
float cubicPulse( float c, float w, float x ){
    x = abs(x - c);
    if( x>w ) return 0.0;
    x /= w;
    return 1.0 - x*x*(3.0-2.0*x);
}

float plot(vec2 st, float pct){
    return  smoothstep( pct-0.02, pct, st.y) -
    smoothstep( pct, pct+0.02, st.y);
}

float nRing = uNRing;
vec3 ringColor = vec3(uRingColor.r,uRingColor.g,uRingColor.b);
void main(){
    // basic lambertian lighting
    vec3 lightDirection = normalize(vecPosition.xyz - uLightPosition);
    float dProd = max(0.3, dot(vecNormal, lightDirection));

    //color
    vec4 color = uMaterialColor;
    float inc = 1.0/nRing;
    float padding = 0.0;
    //draw the rings
    for (int i = 0; i< nRing; i++) {
        float y = cubicPulse(mod(uThreshold*uScale, 1.0),uThickness,st.y-padding);
        //float y = cubicPulse(mod(uTime * 0.5,0.99),uScale,st.y-padding);
        color += vec4(vec3(ringColor)*vec3(y), 1.0);
        padding += inc;
    }
    if (uUseLight >= 0.5) {
        vec4 col = vec4( vec3( dProd ) * vec3( color ), 1.0 );
        fragColor = col;
    } else {
        vec4 col = vec4( vec3( color ), 1.0 );
        fragColor = col;
    }
}