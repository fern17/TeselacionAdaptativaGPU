#version 400

layout (location = 0) in vec3 in_Position;

out vec3 VPosition;
void main(void) {
    VPosition = in_Position;
        //VPosition = vec4(in_Position, 1.0);
    //gl_Position = vec4(in_Position, 1.0);
}

