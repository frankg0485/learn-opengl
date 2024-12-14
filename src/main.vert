#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
    // gl_Position holds the output of the vertex shader
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}