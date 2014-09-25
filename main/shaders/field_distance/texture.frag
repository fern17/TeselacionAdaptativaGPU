#version 420
in vec2 TETexCoord;

uniform sampler2D noisetexture;
layout (location = 0) out vec4 FragColor;
void main(void) {
    FragColor = vec4(texture(noisetexture, TETexCoord).xyz, 1.0);
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0); 
}


