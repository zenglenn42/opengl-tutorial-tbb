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
#define GLDEBUG         // Should produce green triangle when defined.

#include <iostream>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "gldebug.h"

int main(int argc, char** argv)
{
    Display display(600, 600, "Hello World!");
    
    Vertex vertices[] =
    {
        // NB: Vertices specified in counter-clockwise order are
        //     interpreted as front-facing by convention.
        //
        // This is important to know if your code culls back-facing vertices
        // and you mistakenly specify them in clockwise order ...
        // and now are wondering why your rendering window is blank. :-/

        Vertex(glm::vec3(-0.5, -0.5, 0.0)),
        Vertex(glm::vec3( 0.5, -0.5, 0.0)),
        Vertex(glm::vec3( 0.0,  0.5, 0.0))
    };
    
    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
    
#ifdef GLDEBUG
    Shader shader("Resources/debugShader");
#else
    Shader shader("Resources/basicShader");
#endif
    
    while (!display.IsClosed())
    {
        display.Clear(0.2f, 0.3f, 0.8f, 1.0f);
        shader.Bind();
#ifdef GLDEBUG
        // Drive your shaders with legacy-specified mesh.
        glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f(0.5, -0.5, 0.0);
        glVertex3f(0.0f, 0.5f, 0.0f);
        glEnd();
#else
        mesh.Draw();
#endif
        display.Update();
    }
    return 0;
}
