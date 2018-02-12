//
//  mesh.h
//  opengl-tutorial-tbb
//

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex
{
public:
    Vertex(const glm::vec3& pos) {
        this->pos = pos;
    }
    
    glm::vec3* GetPos() { return &pos; }
    
private:
    glm::vec3 pos;
};

class Mesh
{
public:
    Mesh(Vertex vertices[], unsigned int numVertices);
    
    void Draw();
    
    virtual ~Mesh();
private:
    Mesh(const Mesh& other);
    void operator=(const Mesh& other);
    static const unsigned int NUM_BUFFERS = 1;
    enum {
        POSITION_VB,
    };
    
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif // MESH_H
