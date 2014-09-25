#version 400

layout( triangles ) in;
layout( triangle_strip, max_vertices = 3 ) out;

in vec3 TENormal[];
in vec4 TEPosition[];
in float TETessLevel[];

noperspective out vec3 EdgeDistance;
out vec3 Normal;
out vec4 Position;
out float TessLevel;

uniform mat4 ModelViewMatrix;  
uniform mat4 ViewportMatrix;  
uniform mat4 MVPMatrix;  

void main() {
    vec4 t0 = TEPosition[0];
    vec4 t1 = TEPosition[1];
    vec4 t2 = TEPosition[2];
    vec3 p0 = vec3(ViewportMatrix * (t0/t0.w));
    vec3 p1 = vec3(ViewportMatrix * (t1/t1.w));
    vec3 p2 = vec3(ViewportMatrix * (t2/t2.w));

    float a = length(p1 - p2);
    float b = length(p2 - p0);
    float c = length(p1 - p0);
    float alpha = acos( (b*b + c*c - a*a) / (2.0*b*c) );
    float beta = acos( (a*a + c*c - b*b) / (2.0*a*c) );
    float ha = abs( c * sin( beta ) );
    float hb = abs( c * sin( alpha ) );
    float hc = abs( b * sin( alpha ) );

    EdgeDistance = vec3( ha, 0, 0 );
    Normal = TENormal[0];
    Position = MVPMatrix*TEPosition[0];
    TessLevel = TETessLevel[0];
    gl_Position = Position;
    EmitVertex();

    EdgeDistance = vec3( 0, hb, 0 );
    Normal = TENormal[1];
    Position = MVPMatrix*TEPosition[1];
    TessLevel = TETessLevel[1];
    gl_Position = Position;
    EmitVertex();

    EdgeDistance = vec3( 0, 0, hc );
    Normal = TENormal[2];
    Position = MVPMatrix*TEPosition[2];
    TessLevel = TETessLevel[2];
    gl_Position = Position;
    EmitVertex();

    EndPrimitive();
}
