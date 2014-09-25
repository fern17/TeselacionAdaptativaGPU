#version 400

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
out vec3 VSPosition;
out vec3 VSNormal;
uniform mat4 MVPMatrix;
void main(void) {
    gl_Position = MVPMatrix*vec4(in_Position, 1.0);
    VSPosition = in_Position;
    VSNormal = in_Normal;
}

