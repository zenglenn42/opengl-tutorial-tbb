//
//  main.cpp
//  opengl-tutorial-tbb
//

#include <iostream>
#include "display.h"
#include "shader.h"
#include "mesh.h"

int main(int argc, char** argv)
{
    Display display(800, 600, "Hello World!");
    
    Vertex vertices[] =
    {
        Vertex(glm::vec3(-0.5, -0.5, 0.0)),
        Vertex(glm::vec3( 0.0,  0.5, 0.0)),
        Vertex(glm::vec3( 0.5, -0.5, 0.0))
    };
    
    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
    Shader shader("./Resources/basicShader");
    
    while (!display.IsClosed()) {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
        
        shader.Bind();
        mesh.Draw();
        
        display.Update();
    }
    return 0;
}
