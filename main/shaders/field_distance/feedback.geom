#version 420

//layout( triangles ) in;
//layout( triangle_strip, max_vertices = 3 ) out;
layout( points ) in;
layout( points, max_vertices = 1 ) out;
layout( location = 0 ) out vec2 Position;
layout( location = 1 ) out vec2 Field;
layout( location = 2 ) out vec2 FieldR;
layout( location = 3 ) out vec2 FieldRB;
layout( location = 4 ) out vec2 FieldB;


in vec2 VPosition[];
in vec2 VField[];
in vec2 VFieldR[];
in vec2 VFieldRB[];
in vec2 VFieldB[];

//out vec2 Position;
//out vec2 Field;

void main() {
    Position = VPosition[0];
    Field = VField[0];
    FieldR = VFieldR[0];
    FieldRB = VFieldRB[0]; 
    FieldB = VFieldB[0];
    //gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    EndPrimitive();
}
