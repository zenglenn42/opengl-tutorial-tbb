//
//  main.cpp
//  opengl-tutorial-tbb
//


// Struggling to get this to render a red triangle on your platform?
//
// Uncomment the following #define to drive data through debug shaders.
// If that works, then start tweaking the code to enable more of the
// non-debug code until you see a failure and can debug /that/.
//
//#define GLDEBUG         // Should produce green triangle when defined.

#include <iostream>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "gldebug.h"

int main(int argc, char** argv)
{
    Display display(800, 600, "Hello World!");
    
    Vertex vertices[] = {
        glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3( 0.0f,  0.5f, 0.0f), glm::vec2(0.5f, 1.0f),
        glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)
    };
    
    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
    
    Shader shader("Resources/basicShader");
    Texture texture("Resources/bricks.jpg");
    shader.Bind();
    texture.Bind(0);
    
    while (!display.IsClosed())
    {
        display.Clear(0.2f, 0.3f, 0.8f, 1.0f);
        mesh.Draw();
        display.Update();
    }
    return 0;
}
