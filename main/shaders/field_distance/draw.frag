#version 420
in vec2 UV;

uniform sampler2D outtexture;
uniform sampler2D accumtexture;

layout (location = 0) out vec4 FragColor;
void main(void) {
    vec3 mixi = 0.5*texture(outtexture, UV).xyz + 0.5*texture(accumtexture, UV).xyz;
    //mixi = texture(outtexture, UV).xyz;
    FragColor = vec4(mixi , 1.0);
}
