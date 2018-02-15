//
//  mesh.cpp
//  opengl-tutorial-tbb
//

#include "mesh.h"
#include "gldebug.h"

Mesh::Mesh(Vertex * verts, unsigned int numVerts)
{
    m_drawCount = numVerts;
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);
    
    glGenBuffers(1, &m_vertexArrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(Vertex), verts, GL_STATIC_DRAW);
    
    // schema for position data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    
    // schema for texture coordinate data
    glEnableVertexAttribArray(1);
    void * texcoordOffset = (void *)(3 * sizeof(float));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), texcoordOffset);
    
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
    GLCall(glBindVertexArray(m_vertexArrayObject));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, m_drawCount));
    GLCall(glBindVertexArray(0));
}
