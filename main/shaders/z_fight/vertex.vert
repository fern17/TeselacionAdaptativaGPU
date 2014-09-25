#version 400

layout (location = 0) in vec3 in_Position;
out vec3 VPosition;

void main(void) {
    VPosition = in_Position;
}

