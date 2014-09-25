#version 420

//layout( triangles ) in;
//layout( triangle_strip, max_vertices = 3 ) out;
layout( points ) in;
layout( points, max_vertices = 1 ) out;
layout( location = 0 ) out vec2 Position;
layout( location = 1 ) out vec2 Field;


in vec2 TEPosition[];
in vec2 TEField[];
//in vec2 VPosition[];
//in vec2 VField[];

uniform mat4 MVPMatrix;
//out vec2 Position;
//out vec2 Field;

void main() {
    //Position = vec4(TEPosition[0], 0.0, 1.0) *MVPMatrix;
    Position = TEPosition[0];
    Field = TEField[0];
    //Position = VPosition[0];
    //Field = VField[0];
    //gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    EndPrimitive();
}
