#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <Shader.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLuint init_VAO() {
    // all coordinates must be in [-1, 1] range
    vector<float> vertices = {
        -.5f, -.5f, 0, 1, 0, 0,
        .5f, -.5f, 0, 0, 1, 0,
        .5f, .5f, 0, 0, 0, 1,
        -.5f, .5f, 0, 1, 0, 1,
    };

    // vertex indices for the rectangle
    vector<uint> indices = {
        0, 3, 2,
        0, 2, 1
    };


    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO); // generate 1 buffer, and store the ID in VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // can only bind one buffer per type

    // copy the vertices array into the buffer's memory
    // GL_STREAM_DRAW: set once, GPU uses few times
    // GL_STATIC_DRAW: set once, GPU uses many times
    /// GL_DYNAMIC_DRAW: set many times, GPU uses many times
    // cout << vertices.size() * sizeof(float) << endl;
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices), indices.data(), GL_STATIC_DRAW);

    // position 0, 3 values per attribute, float type, don't normalize,
    // position of next data, pointer to start of data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    // enable attribute at location 0
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // on macOS, the actual dimensions aren't 800 by 600
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window) {
        cout << "glfw window create failed" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cout << "glad init failed" << endl;
        glfwTerminate();
        return -1;
    }

    // get the actual initial fb dimensions
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    cout << "Initial framebuffer size: " << fbWidth << " x " << fbHeight << endl;
    glViewport(0, 0, fbWidth, fbHeight);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shaderProgram("../src/main.vert", "../src/main.frag");
    if (shaderProgram.getProgramID() == -1) return 1;

    GLuint shaderProgramID = shaderProgram.getProgramID();

    GLuint VAO;
    VAO = init_VAO();

    // wireframe mode: GL_LINE
    // fill mode: GL_FILL
    // front face is CCW vertices
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window)) {
        // check input
        processInput(window);

        // rendering commands
        glClearColor(.2f, .3f, .3f, 1.f); // set the color
        glClear(GL_COLOR_BUFFER_BIT); // color, depth, or stencil buffer

        // vary uniform with time
        float time = glfwGetTime();
        float val = (sin(time) / 2.f) + .5f;
        int globalColorLoc = glGetUniformLocation(shaderProgramID, "globalColor");

        // must use program before updating uniform
        shaderProgram.use(); 
        glUniform4f(globalColorLoc, 0, val, 0, 1);

         // draw triangle
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3); // triangles, start index of vertex array, 3 vertices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window); // swap back buffer to the front
        glfwPollEvents(); // mouse, keyboard, etc.
    }

    glfwTerminate();
    return 0;
}