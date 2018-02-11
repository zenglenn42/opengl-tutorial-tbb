//
//  main.cpp
//  opengl-tutorial-tbb
//

#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"

int main(int argc, const char * argv[]) {
    Display display(800, 600, "Hello World");
    
    Shader shader("./Resources/basicShader");
    
    while (!display.IsClosed()) {
        display.Clear(0.2f, 0.3f, 0.8f, 1.0f);
        display.Update();
    }
    return 0;
}
