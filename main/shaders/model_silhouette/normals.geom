#version 400

layout( points ) in;
layout( line_strip, max_vertices = 2 ) out;

in vec3 VSPosition[];
in vec3 VSNormal[];
uniform mat4 MVPMatrix;
uniform float NormScale;
void main() {
    vec4 v0 = vec4(VSPosition[0], 1.0);
    gl_Position = MVPMatrix*v0;
    EmitVertex();
    
    vec4 v1 = v0 + vec4(VSNormal[0], 0.0)*NormScale;
    gl_Position = MVPMatrix * v1;
    EmitVertex();

    EndPrimitive();
}
