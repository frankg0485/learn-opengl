#include "Shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string read_file(string filename) {
    ifstream vertex_shader_file(filename);
    if (!vertex_shader_file) {
        cerr << "couldn't find file " << filename << endl;
        return "";
    }

    stringstream buffer;
    buffer << vertex_shader_file.rdbuf();
    return buffer.str();
}

GLuint add_shader(string filename, GLuint type, char infoLog[], uint infoLogSize) {
    string code_ptr = read_file(filename);
    const char *shader_code = code_ptr.c_str(); 

    GLuint shader;
    shader = glCreateShader(type);

    // attach glsl code to shader (pass 1 string as the source code)
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, infoLogSize, NULL, infoLog);
        return -1;
    }

    return shader;
}

Shader::Shader(const string &vertexPath, const string &fragmentPath) {
    char infoLog[512];
    GLuint vertexShader, fragShader;
    if ((vertexShader = add_shader(vertexPath.c_str(), GL_VERTEX_SHADER, infoLog, sizeof(infoLog))) == -1) {
        cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
        ID = -1;
        return;
    }
    if ((fragShader = add_shader(fragmentPath.c_str(), GL_FRAGMENT_SHADER, infoLog, sizeof(infoLog))) == -1) {
        cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
        ID = -1;
        return;
    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cerr << "ERROR::PROGRAM::SHADER_LINKING_FAILED\n" << infoLog << endl;
        ID = -1;
        return;
    }

    // after linking them to the program, don't need shaders anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    ID = shaderProgram;
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const string &name, bool value) const {
    int boolLoc = glGetUniformLocation(ID, name.c_str());
    if (boolLoc == -1) {
        cerr << "ERROR::PROGRAM::SET_BOOL_FAILED " << name << endl;
    }

    glUniform1i(boolLoc, (int) value);
}

void Shader::setInt(const string &name, int value) const {
    int intLoc = glGetUniformLocation(ID, name.c_str());
    if (intLoc == -1) {
        cerr << "ERROR::PROGRAM::SET_BOOL_FAILED " << name << endl;
    }

    glUniform1i(intLoc, value);  
}

void Shader::setFloat(const string &name, float value) const {
    int floatLoc = glGetUniformLocation(ID, name.c_str());
    if (floatLoc == -1) {
        cerr << "ERROR::PROGRAM::SET_BOOL_FAILED " << name << endl;
    }

    glUniform1f(floatLoc, value);
}

unsigned int Shader::getProgramID() const { return ID; }