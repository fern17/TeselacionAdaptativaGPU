#version 400

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
out vec3 VPosition;
out vec3 VNormal;
uniform mat4 MVPMatrix;
void main(void) {
    VPosition = in_Position;
    VNormal = in_Normal;
    //gl_Position =  MVPMatrix * vec4(in_Position, 1.0);
}

