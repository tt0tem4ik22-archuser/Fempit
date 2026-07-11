#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>
#include <ostream>

#include "headers.h"

using namespace std;


unsigned int LoadTexture(const char* path) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "ERROR: failed to load texture " << path << endl;
    }
    stbi_image_free(data);
    return texture;
}