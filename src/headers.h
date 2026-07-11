#pragma once
#ifndef HEADERS_H
#define HEADERS_H
#include <vector>

const float pi = 3.14159265358979;

unsigned int GenShaders(); 
unsigned int LoadTexture(const char* path); 
int OpenWindow(const char* name, int width, int height); 

#endif
