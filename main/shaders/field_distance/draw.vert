#version 420

layout (location = 0) in vec3 in_Position;
out vec2 UV;
uniform mat4 MVPMatrix;

void main(void) {
    //Notar que la matriz no se usa porque los vertices ya vienen en -1,1
    gl_Position = vec4(in_Position,  1.0);
    UV = (in_Position.xy+vec2(1,1))/2.0;
}

