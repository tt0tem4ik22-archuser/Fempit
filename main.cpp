#include <iostream>
#include "src/headers.h"

using namespace std;


int main() {
    string name = "FempitEngine v0.0.1dev";
    const char* charname = name.c_str();
    OpenWindow(charname, 800, 600);
    return 0;
}