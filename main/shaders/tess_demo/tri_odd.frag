#version 400

vec4 TriColor = vec4(0.0, 0.0, 1.0, 1.0);

layout (location = 0) out vec4 FragColor;
void main() {
    FragColor = TriColor;
}
