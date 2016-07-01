#version 150
//Modes: uncomment to active one modes
//#define SIMPLE_MIX
//#define PLOT
#define COLOR_DEPENDING_ON_MESH_HEIGHT

in vec3 vecNormal;
in vec4 vecPosition;
in float height;

out vec4 fragColor;

// this are set in the OF app
uniform vec3 uLightPosition;
uniform vec4 uMaterialColor;
uniform float uTime;
uniform vec2 uResolution;

// Only used when PLOT
float plot (vec2 st, float pct){
    return  smoothstep( pct-0.01, pct, st.y) -
    smoothstep( pct, pct+0.01, st.y);
}

void main(){
    // basic lambertian lighting
    vec3 lightDirection = normalize(vecPosition.xyz - uLightPosition);
    float dProd = max(0.0, dot(vecNormal, lightDirection));

    //color
    // the default is the material color
    vec4 color = uMaterialColor;
    vec4 colorA = vec4(0.149,0.141,0.912,1.0);
    vec4 colorB = vec4(1.000,0.833,0.224,1.0);

    #ifdef SIMPLE_MIX
        float pct = abs(sin(uTime));
        color = mix(colorA, colorB, pct);
    #endif

    #ifdef PLOT
        vec2 st = gl_FragCoord.xy/uResolution.xy;
        vec4 black = vec4(vec3(0.0),1.0);
        vec4 pct = vec4(st.x);
        color = mix(colorA, colorB, pct);
        color = mix(color,vec4(1.0,0.0,0.0,1.0),plot(st,pct.r));
        color = mix(color,vec4(0.0,1.0,0.0,1.0),plot(st,pct.g));
        color = mix(color,vec4(0.0,0.0,1.0,1.o),plot(st,pct.b));
    #endif

    #ifdef COLOR_DEPENDING_ON_MESH_HEIGHT
        //just to see how the fragCoord can be used to change the color
        //color.r = gl_FragCoord.y / uResolution.y;
        color = mix(colorA, colorB, height);
    #endif

    vec4 col = vec4( vec3( dProd ) * vec3( color ), 1.0 );
    fragColor = col;
}