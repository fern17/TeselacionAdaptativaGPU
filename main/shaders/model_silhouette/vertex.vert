#version 400

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
//layout (location = 2) in vec3 in_NeighborNormal0;
//layout (location = 3) in vec3 in_NeighborNormal1;
//layout (location = 4) in vec3 in_NeighborNormal2;

out vec3 VPosition;
out vec3 VNormal;
//out vec3 VNN0;
//out vec3 VNN1;
//out vec3 VNN2;

uniform mat4 MVPMatrix;

void main(void) {
    VPosition = in_Position;
    VNormal = in_Normal;
  //VNN0 = in_NeighborNormal0;
  //VNN1 = in_NeighborNormal1;
  //VNN2 = in_NeighborNormal2;
    //gl_Position =  MVPMatrix * vec4(in_Position, 1.0);
}

