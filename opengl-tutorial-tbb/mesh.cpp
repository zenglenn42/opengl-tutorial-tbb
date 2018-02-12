//
//  mesh.cpp
//  opengl-tutorial-tbb
//

#include "mesh.h"
#include "gldebug.h"

Mesh::Mesh(Vertex vertices[], unsigned int numVertices)
{
    m_drawCount = numVertices;
    
    GLCall(glGenVertexArrays(1, &m_vertexArrayObject));
    GLCall(glBindVertexArray(m_vertexArrayObject));
    
    GLCall(glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]));
    GLCall(glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW));
    
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GLCall(glBindVertexArray(0));
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
#ifndef GLDEBUG
    GLCall(glBindVertexArray(m_vertexArrayObject));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, m_drawCount));
    GLCall(glBindVertexArray(0));
#endif
}
