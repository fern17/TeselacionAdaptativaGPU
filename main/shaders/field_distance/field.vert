#version 400

layout (location = 0) in vec2 in_Position;
out vec4 VColor;
uniform mat4 MVPMatrix;
uniform vec4 Color;
void main(void) {
    gl_Position = MVPMatrix*vec4(in_Position, 0.0, 1.0);
    VColor = Color;
}

