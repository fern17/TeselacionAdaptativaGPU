#version 400

layout (location = 0) out vec4 FragColor;
vec3 color = vec3(0.3, 1.0, 0.2);
void main() {
    FragColor = vec4(color, 1.0);
}
