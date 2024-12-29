#version 330 core

in vec4 vertColor;

uniform vec4 globalColor;

out vec4 FragColor;

void main() {
    FragColor = globalColor;//vertColor;//vec4(1.0f, 0.5f, .2f, 1.f);
}