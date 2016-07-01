#version 150

//#define BORDERS
//#define CIRCLE_DISTANCE
#define CIRCLE_SMALL

in vec3 vecNormal;
in vec4 vecPosition;
in vec2 st;

out vec4 fragColor;

// this are set in the OF app
uniform vec3 uLightPosition;
uniform vec4 uMaterialColor;
uniform vec2 uResolution;
uniform float uTime;

void main(){
    // basic lambertian lighting
    vec3 lightDirection = normalize(vecPosition.xyz - uLightPosition);
    float dProd = max(0.3, dot(vecNormal, lightDirection));

    //color
    vec4 color = uMaterialColor;
    #ifdef BORDERS
        //values under 1.0 returns 0.0, more than 0.1 returns 1
        vec2 bordersBottomLeft = step(vec2(0.1),st);
        // this is like and AND condition 1.0 * 1.0 returns 1.0 (black)
        // 0.0 * 0.0 return 0.0 (white)
        float pct = bordersBottomLeft.x * bordersBottomLeft.y;

        // top-right
        vec2 bordersTopRight = step(vec2(0.1),1.0-st);
        pct *= bordersTopRight.x * bordersTopRight.y;

        color = vec4(vec3(pct), 1.0);
    #endif

    #ifdef CIRCLE_DISTANCE
        //to draw a circle you need to compare each point with the center.
        // you can use the function distance, length or sqrt.
        // this time we use screen cordinates
        float pct = 0.0;
        vec2 stscreen = gl_FragCoord.xy/uResolution;
        //The closer a pixel is to the center, the lower (darker) value it has
        pct = distance(stscreen,vec2(0.5));
        color = vec4(pct);
    #endif


    #ifdef CIRCLE_SMALL
        float pct = 0.0;
        vec2 stscreen = gl_FragCoord.xy/uResolution;
        pct = distance(stscreen,vec2(0.5, 0.7));
        color = vec4(step(pct, abs(sin(uTime)*0.1)));
    #endif



    // The multiplication of left*bottom will be similar to the logical AND.
    //vec4 color = vec4( left * bottom );
    vec4 col = vec4( vec3( dProd ) * vec3( color ), 1.0 );
    fragColor = col;
}