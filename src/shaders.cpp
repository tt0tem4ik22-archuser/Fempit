#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
#include <fstream>      
#include <sstream>      

#include "headers.h"

using namespace std;


unsigned int GenShaders() {
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 VertexPos;\n"
        "layout (location = 1) in vec3 VertexColor;\n"
        "layout (location = 2) in vec2 VertexTexCoord;\n"
        "out vec3 Color;\n"
        "out vec2 TexCoord;\n"
        "uniform float scr_aspect;\n"
        "void main() {\n"
        "   gl_Position = vec4(VertexPos.x*scr_aspect, VertexPos.y, VertexPos.z, 1.0);\n"
        "   Color = VertexColor;\n"
        "   TexCoord = VertexTexCoord;\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "in vec3 Color;\n"
        "in vec2 TexCoord;\n"
        "out vec4 FragColor;\n"
        "uniform sampler2D Texture;\n"
        "void main() {\n"
        "   FragColor = texture(Texture, TexCoord);\n"
        "}\0";

    int success;
    char infoLog[512];
    
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
        return 0;
    }
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
        return 0;
    }
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}
