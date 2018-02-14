//
//  mesh.cpp
//  opengl-tutorial-tbb
//

#include "mesh.h"
#include "gldebug.h"

Mesh::Mesh(Vertex vertices[], unsigned int numVertices)
{
    m_drawCount = numVertices;
    
    // Setup for describing our data buffer structure.

    GLCall(glGenVertexArrays(1, &m_vertexArrayObject));
    GLCall(glBindVertexArray(m_vertexArrayObject));
    
    // Allocate and fill our GPU buffer with mesh data (i.e., position vertices).

    GLCall(glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]));
    GLCall(glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW));
    
    // Describe the layout of our buffer data.

    GLint pos_attrib_index = 0;       // For each vertex, we specify position first at
                                      // offset 0.

    bool vertex_stride = 0;           // Space in bytes between consecutive vertices.
                                      // Use 0, by convention, for tightly packed position data
                                      // (no interleaved color or texture attributes here).

    GLint pos_components = 3;         // Position is comprised of the components, x, y, z.

    bool pos_normalized = GL_FALSE;   // Only applies to normalizing fixed-point
                                      // data before converting it to floating-point.

    GLCall(glEnableVertexAttribArray(pos_attrib_index));
    GLCall(glVertexAttribPointer(pos_attrib_index, 
            pos_components, 
            GL_FLOAT, 
            pos_normalized,
            vertex_stride,
            (const void*)0));         // pointer to first position attribute within the buffer.

    GLCall(glBindVertexArray(0));     // Unbind vertex array.
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
