//
//  mesh.h
//  opengl-tutorial-tbb
//

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoord;
};

class Mesh
{
public:
    Mesh(Vertex * verts, unsigned int numVerts);
    void Draw();
    ~Mesh();
private:
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffer;
    unsigned int m_drawCount;
};

#endif // MESH_H
