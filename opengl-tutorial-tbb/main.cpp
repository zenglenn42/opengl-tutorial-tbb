//
//  main.cpp
//  opengl-tutorial-tbb
//

// Want to check glError on most of your OpenGL calls?
//
// Then uncomment this macro.
//#define GLDEBUG

#include <iostream>
#include <glm/glm.hpp>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "gldebug.h"

const int WIDTH  = 800;
const int HEIGHT = 600;

const glm::vec4 Blue = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);
const glm::vec4 Green = glm::vec4(0.0f, 0.8f, 0.3f, 1.0f);

int main(int argc, char** argv)
{
    Display display(WIDTH, HEIGHT, "Hello World!");
    
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3( 0.0f,  0.5f, 0.0f), glm::vec2(0.5f, 1.0f)),
        Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f))
    };
    
    unsigned int indices[] = {0, 1, 2};
    
    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    Mesh mesh2("./Resources/monkey3.obj");
    
    Shader shader("Resources/basicShader");
    const glm::vec4 backgroundColor = Blue;
    Texture texture("Resources/bricks.jpg");
    Camera camera(glm::vec3(0.0f, 0.0f, -4.0f),
                  70.0f,
                  (float)WIDTH /(float)HEIGHT,
                  0.01f,
                  1000.0f);
    Transform transform;

    float counter = 0.0f;
    while (!display.IsClosed())
    {
        display.Clear(backgroundColor);
        float sinCounter = sinf(counter);
        float cosCounter = cosf(counter);
        
        transform.GetPos().x = sinCounter;
        transform.GetPos().z = cosCounter;
        transform.GetRot().x = counter;
        transform.GetRot().y = counter;
        transform.GetRot().z = counter;
        //transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
        
        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);
        mesh2.Draw();
        
        display.Update();
        counter += 0.01f;
    }
    return 0;
}
