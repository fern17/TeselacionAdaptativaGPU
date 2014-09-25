#version 400

out vec4 FragColor;
uniform bool UseIllumination;

void main(void) {
    if (UseIllumination)
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    else
        discard;
}
