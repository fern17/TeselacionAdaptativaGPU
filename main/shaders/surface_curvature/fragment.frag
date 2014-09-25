#version 400

noperspective in vec3 EdgeDistance;
in vec3 Normal;
in vec4 Position;
in float TessLevel;
uniform bool UseIllumination;
uniform bool UseTessColoration;
uniform vec3 CamPos;
uniform float MaxTess;
uniform sampler2D TexColorMap;

layout ( location = 0 ) out vec4 FragColor;

float LineWidth = 0.3f;
//vec4 LineColor = vec4(0.0, 0.12, 1.0, 1.0);
vec4 LineColor = vec4(0.0, 0.0, 0.0, 1.0);

vec3 emission_m = vec3(0.5, 0.5, 0.5);
vec3 ambient_lm = vec3(1.0, 1.0, 1.0);
vec3 ambient_l  = vec3(1.0, 1.0, 1.0);
vec3 ambient_m  = vec3(0.8, 0.2, 0.0);
vec3 diffuse_l  = vec3(1.0, 1.0, 1.0);
vec3 diffuse_m  = vec3(0.5, 0.5, 0.5);
vec3 specular_l = vec3(1.0, 1.0, 1.0);
vec3 specular_m = vec3(0.8, 0.8, 0.8);
float shininess = 1.0;
vec3 light_pos = vec3(0.0, 0.0, 5.0);


//vec3 emission_m = vec3(0.5, 0.5, 0.0);
//vec3 ambient_lm = vec3(1.0, 1.0, 1.0);
//vec3 ambient_l  = vec3(1.0, 1.0, 1.0);
//vec3 diffuse_l  = vec3(1.0, 1.0, 1.0);
//vec3 specular_l = vec3(1.0, 1.0, 1.0);
//vec3 light_pos = vec3(0.0, 0.0, -5.0);
//float shininess = 1.0;
//vec3 ambient_m  = vec3(1.0, 0.0, 0.0);
//vec3 diffuse_m  = vec3(1.0, 0.0, 0.0);
//vec3 specular_m = vec3(1.0, 1.0, 1.0);
vec3 COLOR_RED = vec3(1.0, 0.0, 0.0);
vec3 COLOR_BLUE = vec3(0.0, 0.0, 1.0);
vec4 PhongShading(vec3 pos, vec3 norm) {
    vec3 L = normalize(light_pos-pos); 
    vec3 ve = normalize(CamPos-pos);
    vec3 s = normalize(L+ve); 
    vec3 first_term = emission_m + ambient_lm*ambient_m;
    vec3 second_term = ambient_l*ambient_m +
                       diffuse_l*diffuse_m*max(dot(L,norm), 0.0) +
                       specular_l*specular_m*pow(max(dot(s, norm), 0.0), shininess);
    vec3 out_color = first_term + second_term;
    return vec4(out_color, 1.0);
}

float edgeMix() {
    // Find the smallest distance
    float d = min( min( EdgeDistance.x, EdgeDistance.y ), EdgeDistance.z );

    if( d < LineWidth - 1 ) {
        return 1.0;
    } else if( d > LineWidth + 1 ) {
        return 0.0;
    } else {
        float x = d - (LineWidth - 1);
        return exp2(-2.0 * (x*x));
    }
}

void main() {
    //if (!gl_FrontFacing) { //Descarte prematuro de fragmentos que no se estan viendo
    //No se hace porque el modelo no es cerrado, se ven los poligonos backface
    //    discard;
    //    return;
    //}
    float mixVal = edgeMix();
    vec4 color;
    if (UseIllumination) {
        color = PhongShading( Position.xyz, Normal );
    } else { 
        color = vec4(ambient_m, 1.0);
    }
    
    color = pow( color, vec4(1.0/2.2) );
    FragColor = color;

    if (UseTessColoration) {
        float scale_log = (log2(TessLevel)/log2(MaxTess)); //escalado por el nivel de teselacion
        float scale = (TessLevel/MaxTess); //escalado por el nivel de teselacion
        vec4 colorMapVal = vec4(texture(TexColorMap, vec2(scale, 0.0)).rgb, 1.0);
        //vec4 color_tc = vec4(mix(COLOR_BLUE, COLOR_RED, scale_log), 1.0);
        //FragColor = colorMapVal;
        FragColor = mix(FragColor, colorMapVal, 0.75);
    }

    FragColor = mix( FragColor, LineColor, mixVal );
}
