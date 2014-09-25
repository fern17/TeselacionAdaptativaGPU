#version 400

layout (location = 0) in vec2 in_Position;
out vec2 VPosition;

void main(void) {
    VPosition = in_Position;
}

