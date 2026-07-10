#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.h"

using namespace std;


int OpenWindow(const char* name) {
    if (!glfwInit()) {
        return -1;  
    } 

    GLFWwindow* window = glfwCreateWindow(800, 600, name, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

