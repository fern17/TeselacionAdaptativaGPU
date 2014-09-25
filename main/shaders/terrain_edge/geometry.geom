#version 400

layout( triangles ) in;
layout( triangle_strip, max_vertices = 3 ) out;

in vec3 TENormal[];
in vec4 TEPosition[];
in vec3 TEWorldPosition[];
in vec2 TETex[];
in float TETexMixVal[];
in float TETessLevel[];

noperspective out vec3 EdgeDistance;
out vec3 Normal;
out vec4 Position;
out vec3 WorldPosition;
out vec2 TexCoord;
out float TexMixVal;
out float TessLevel;
uniform mat4 ViewportMatrix;  // Viewport matrix

void main()
{
    // Transform each vertex into viewport space
    vec2 p0 = vec2(ViewportMatrix * (gl_in[0].gl_Position / gl_in[0].gl_Position.w));
    vec2 p1 = vec2(ViewportMatrix * (gl_in[1].gl_Position / gl_in[1].gl_Position.w));
    vec2 p2 = vec2(ViewportMatrix * (gl_in[2].gl_Position / gl_in[2].gl_Position.w));

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
    Position = TEPosition[0];
    WorldPosition = TEWorldPosition[0];
    TexCoord = TETex[0];
    TexMixVal = TETexMixVal[0];
    TessLevel = TETessLevel[0];
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    EdgeDistance = vec3( 0, hb, 0 );
    Normal = TENormal[1];
    Position = TEPosition[1];
    WorldPosition = TEWorldPosition[1];
    TexCoord = TETex[1];
    TexMixVal = TETexMixVal[1];
    TessLevel = TETessLevel[0];
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    EdgeDistance = vec3( 0, 0, hc );
    Normal = TENormal[2];
    Position = TEPosition[2];
    WorldPosition = TEWorldPosition[2];
    TexCoord = TETex[2];
    TexMixVal = TETexMixVal[2];
    TessLevel = TETessLevel[0];
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}
