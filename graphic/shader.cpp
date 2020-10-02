#include "shader.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
using namespace wippi::graphic;

shader::shader()
    : id(glCreateProgram())
{}

GLuint shader::pid()
{
    return this->id;
}

void shader::attach()
{
    for (GLuint& id: this->ids) {
        glAttachShader(this->id, id);
    }
}

void shader::detach()
{
    for (GLuint& id: this->ids) {
        glDetachShader(this->id, id);
        glDeleteShader(id);
    }
}

void shader::link()
{
    this->attach();

    GLint res;
    GLint len;
    glLinkProgram(this->id);
    glGetProgramiv(this->id, GL_LINK_STATUS, &res);
    glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &len);

    if (len > 0) {
        vector<char> msg;
        glGetProgramInfoLog(this->id, len, NULL, &msg[0]);
        cerr << "Failed to link program\n" << endl;
    }

    this->detach();
}

void shader::compile(GLuint id, const char* file)
{
    ifstream ifs(file);
    string str((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    const char* ptr = str.c_str();

    glShaderSource(id, 1, &ptr, NULL);
    glCompileShader(id);

    GLint res;
    GLint len;

    glGetShaderiv(id, GL_COMPILE_STATUS, &res);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

    if (len > 0) {
        vector<char> msg(len+1);
        glGetShaderInfoLog(id, len, NULL, &msg[0]);
        cout << &msg[0] << "\n" << endl;
    }

    this->ids.push_back(id);
}
