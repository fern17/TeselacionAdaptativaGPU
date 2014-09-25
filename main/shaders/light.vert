#version 400

layout (location = 0) in vec3 in_Position;

uniform mat4 MVPMatrix;
void main(void) {
    gl_Position = MVPMatrix*vec4(in_Position, 1.0);
}

