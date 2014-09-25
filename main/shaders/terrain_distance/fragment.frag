#version 400

noperspective in vec3 EdgeDistance;
in vec3 Normal;
in vec4 Position;
in vec3 WorldPosition;
in vec2 TexCoord;
in float TexMixVal;
in float TessLevel;
out vec4 FragColor;

//Datos para el wireframe
float LineWidth = 1.0f;
vec4 LineColor = vec4(0.0, 0.0, 0.0, 1.0);

//Datos de la Luz (la posicion viene por uniform para poder moverla)
uniform vec4 LightPosition;
uniform float HorizScale;
uniform vec3 CamPos;

vec3 FogColor = vec3(0.6, 0.6, 0.6);
float FogDensity = 2.0;

//Bool para decidir si se dibujan ciertas cosas o no
uniform bool DrawWire;
uniform bool UseIllumination;
uniform bool UseTexture;
uniform bool UseFog;
uniform bool UseTessColoration;
uniform float MaxTess;

//Texturas para darle color
uniform sampler2D TexRock;
uniform sampler2D TexGrass;
uniform sampler2D TexColorMap;

vec3 emission_m = vec3(0.5, 0.5, 0.0);
vec3 ambient_lm = vec3(1.0, 1.0, 1.0);
vec3 ambient_l  = vec3(1.0, 1.0, 1.0);
vec3 diffuse_l  = vec3(1.0, 1.0, 1.0);
vec3 specular_l = vec3(1.0, 1.0, 1.0);
vec3 light_pos = LightPosition.xyz;
float shininess = 1.0;
vec3 ambient_m  = vec3(1.0, 1.0, 1.0);
vec3 diffuse_m  = vec3(1.0, 1.0, 1.0);
vec3 specular_m = vec3(1.0, 1.0, 1.0);

vec3 COLOR_RED = vec3(1.0, 0.0, 0.0);
vec3 COLOR_BLUE = vec3(0.0, 0.0, 1.0);

vec4 PhongShading(vec3 pos, vec3 norm) {
    vec3 L = normalize(light_pos-pos); 
    vec3 ve = normalize(CamPos-pos);
    vec3 s = normalize(L+ve); 
    vec3 first_term = emission_m + ambient_lm*ambient_m;
    vec3 second_term = ambient_l*ambient_m +
                       diffuse_l*diffuse_m*max(dot(L, norm), 0.0) +
                       specular_l*specular_m*pow(max(dot(s, norm), 0.0), shininess);
    vec3 out_color = first_term + second_term;
    return vec4(out_color, 1.0);
}

//Devuelve un factor de mezcla para dibujar el wireframe encima de las mallas
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

void main(void) {
    if (!gl_FrontFacing) { //Descarte prematuro de fragmentos que no se estan viendo
        discard;
        return;
    }
    float mixVal; //Mezcla entre el color del triangulo y el borde
    if (DrawWire) 
        mixVal = edgeMix();
    else 
        mixVal = 0.0;

    //vec4 color = vec4( diffuseModel( Position.xyz, Normal ), 1.0);
    vec4 color; //Color del modelo de iluminacion
    //if (UseIllumination) color = vec4(ads(), 1.0);
    if (UseIllumination) 
        color = PhongShading(Position.xyz, Normal);
    else 
        color = vec4(0.6, 0.6, 0.9, 1.0);
    //Correccion al color
    color = pow( color, vec4(1.0/2.2) );

    //Mezcla entre el color base y la linea
    FragColor = mix( color, LineColor, mixVal );
 
    if (UseTexture) { //Aplicacion de las texturas al fragmento
        vec4 TexColorRock = vec4(texture(TexRock, TexCoord).rgb, 1.0);
        vec4 TexColorGrass = vec4(texture(TexGrass, TexCoord).rgb, 1.0);
        vec4 TexColor = mix(TexColorGrass, TexColorRock, TexMixVal); 
        FragColor = mix(FragColor, TexColor, 0.85);
    }
    if (UseTessColoration) {
        float scale_log = (log2(TessLevel)/log2(MaxTess)); //escalado por el nivel de teselacion
        float scale = (TessLevel/MaxTess); //escalado por el nivel de teselacion
        vec4 colorMapVal = vec4(texture(TexColorMap, vec2(scale, 0.5)).rgb, 1.0);
        //vec4 color_tc = vec4(mix(COLOR_BLUE, COLOR_RED, scale_log), 1.0);
        //FragColor = colorMapVal;
        FragColor = mix(FragColor, colorMapVal, 0.75);
    }
    if (UseFog) { //Aplicacion de la niebla al fragmento
        float dist = distance(CamPos, WorldPosition)/HorizScale;
        float fogFactor = exp(-pow(FogDensity*dist, 2));
        fogFactor = clamp(fogFactor, 0.0, 1.0);
        if (fogFactor < 0.001){  //Si es muy chico, que haga culling
            discard;
            return;
        }
        else 
            FragColor = mix(FragColor, vec4(FogColor, 1.0), 1.0-fogFactor);
    }
    
}
