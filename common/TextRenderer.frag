#version 400
 
in vec2 texcoord;
layout (location = 0) out vec4 FragColor; 

uniform sampler2D tex;
uniform vec4 color;

void main(void) {
  FragColor = vec4(1.0, 1.0, 1.0, texture(tex, texcoord).r) * color;
}
