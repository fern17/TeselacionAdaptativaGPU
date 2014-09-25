#version 420

layout (location = 0) in vec2 in_Position;
layout (location = 1) in vec2 in_Field;
layout (location = 2) in vec2 in_FieldRight;
layout (location = 3) in vec2 in_FieldRightBottom;
layout (location = 4) in vec2 in_FieldBottom;
layout (location = 5) in vec2 in_PositionOriginal; //la posicion original de los vertices, antes de que se muevan
out vec2 VPosition;
out vec2 VField;
out vec2 VFieldR;
out vec2 VFieldRB;
out vec2 VFieldB;
out vec2 VPositionOriginal;
uniform mat4 MVPMatrix;
uniform float StepH;

void main(void) {
    VPosition = in_Position;
    VField = in_Field;
    VFieldR = in_FieldRight; VFieldRB = in_FieldRightBottom; VFieldB = in_FieldBottom;
    VPositionOriginal = in_PositionOriginal;
    //gl_Position = MVPMatrix*vec4(in_Position, 0.0, 1.0);
}

