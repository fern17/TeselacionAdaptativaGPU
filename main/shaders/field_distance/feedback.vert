#version 420

layout(location = 0) in vec2 in_Position;
layout(location = 1) in vec2 in_Field;
layout(location = 2) in vec2 in_FieldRight;
layout(location = 3) in vec2 in_FieldRightBottom;
layout(location = 4) in vec2 in_FieldBottom;

out vec2 VPosition;
out vec2 VField;
out vec2 VFieldR;
out vec2 VFieldRB;
out vec2 VFieldB;

uniform float StepH;
uniform int FieldId;
vec2 calculateField(vec2 pos, int field_id) {
    vec2 local_field;
    if (field_id == 0) {
        local_field.x = cos(pos.x);
        local_field.y = (pos.y);
    }
    if (field_id == 1) {
        local_field.x =  (pos.x);
        local_field.y = (pos.y);
    }
    if (field_id == 2) {
        local_field.x = sin(pos.x);
        local_field.y = cos(pos.y);
    }
    return local_field;

}


void main(void) {
     vec2 field = calculateField(in_Position, FieldId);
     //vec2 euler1 = in_Position + in_Field*StepH; //Euler 1er orden
     vec2 euler1 = in_Position + field*StepH; //Euler 1er orden
     //float h2 = StepH/2.0;
     //vec2 rk2 = in_Position + h2*in_Field + h2*euler1; //Runge Kutta Orden 2 (Heun) pero esta mal
     VPosition = euler1;
     VField = in_Field; 
     VFieldR = in_FieldRight; 
     VFieldRB = in_FieldRightBottom; 
     VFieldB = in_FieldBottom;
}
