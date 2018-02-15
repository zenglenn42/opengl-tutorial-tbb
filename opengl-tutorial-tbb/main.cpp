//
//  main.cpp
//  opengl-tutorial-tbb
//

// Want to check glError on most of your OpenGL calls?
//
// Then uncomment this macro.
//#define GLDEBUG

// Want to use theBennyBox's implementation as given in Tutorial 4 on youtube?
//
// Then keep this macro defined.  Otherwise an alternate version of the Mesh
// class is built with a single vector array buffer (vab), managed by slightly
// fancier calls to glVertexAttribPointer().
#define TUTORIAL_IMPLEMENTATION

#include <iostream>
#include <glm/glm.hpp>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "gldebug.h"

const glm::vec4 Blue = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);
const glm::vec4 Green = glm::vec4(0.0f, 0.8f, 0.3f, 1.0f);

int main(int argc, char** argv)
{
    Display display(800, 600, "Hello World!");
    
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3( 0.0f,  0.5f, 0.0f), glm::vec2(0.5f, 1.0f)),
        Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f))
    };
    
    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
    
#if defined(TUTORIAL_IMPLEMENTATION)
    Shader shader("Resources/basicShader");
    const glm::vec4 backgroundColor = Blue;
#else
    Shader shader("Resources/altShader");
    const glm::vec4 backgroundColor = Green;
#endif
    Texture texture("Resources/bricks.jpg");
    shader.Bind();
    texture.Bind(0);
    
    while (!display.IsClosed())
    {
        display.Clear(backgroundColor);
        mesh.Draw();
        display.Update();
    }
    return 0;
}
