#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "headers.h"

using namespace std;


int OpenWindow(const char* name, int width, int height) {
    if (!glfwInit()) {
        return -1;  
    } 

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    float vertices[] = {
        //Position            //Color             //Texture coord
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    unsigned int shaderProgram = GenShaders();

    // vertex array
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // vertex buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // draw by position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // draw by color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // draw by texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int EBO;
    glCreateBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // clear buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int texture = LoadTexture("textures/grass.png");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        glUseProgram(shaderProgram);

        int uni_sasp = glGetUniformLocation(shaderProgram, "scr_aspect");
        glUniform1f(uni_sasp, (float)height / width);
        int uni_text = glGetUniformLocation(shaderProgram, "angle");
        glUniform1i(uni_text, 0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

