#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertColor;

void main() {
    // gl_Position holds the output of the vertex shader
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    vertColor = vec4(aColor.rgb, 1);//vec4(0, 1, 1, 1);
}