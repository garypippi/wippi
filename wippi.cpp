#include "graphic/shader.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW//glfw3.h>

using namespace std;
using namespace wippi::graphic;

int close(GLFWwindow* window) {
    return glfwGetKey(window, GLFW_KEY_ESCAPE) + glfwWindowShouldClose(window);
}

int main() {

    glewExperimental = true;

    if (! glfwInit()) {
        cerr << "Failed to initialize GLFW\n" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    GLFWwindow* window = glfwCreateWindow(1024, 768, "", NULL, NULL);

    if (window == NULL) {
        cerr << "Failed to open GLFW window\n" << endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;

    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLFW\n" << endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    const GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f
    };

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    shader shader;
    shader.compile(glCreateShader(GL_VERTEX_SHADER), "graphic/shader/v");
    shader.compile(glCreateShader(GL_FRAGMENT_SHADER), "graphic/shader/f");
    shader.link();

    while (! close(window)) {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader.pid());
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
