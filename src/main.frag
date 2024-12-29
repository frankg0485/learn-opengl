#version 330 core

in vec4 vertColor;

uniform vec4 globalColor;

out vec4 FragColor;

void main() {
    FragColor = vertColor;
}