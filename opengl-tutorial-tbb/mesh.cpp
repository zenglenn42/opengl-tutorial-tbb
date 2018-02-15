//
//  mesh.cpp
//  opengl-tutorial-tbb
//

#include "mesh.h"
#include "gldebug.h"

#if defined(TUTORIAL_IMPLEMENTATION)

#include <vector>

    Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
    {
        m_drawCount = numVertices;
        
        GLCall(glGenVertexArrays(1, &m_vertexArrayObject));
        GLCall(glBindVertexArray(m_vertexArrayObject));
        
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> texCoords;
        
        positions.reserve(numVertices);
        texCoords.reserve(numVertices);
        
        for (unsigned int i = 0; i < numVertices; i++)
        {
            positions.push_back(*vertices[i].GetPos());
            texCoords.push_back(*vertices[i].GetTexCoord());
        }
        
        GLCall(glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
        
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]));
        GLCall(glBufferData(GL_ARRAY_BUFFER,
                     numVertices * sizeof(positions[0]),
                     &positions[0],
                     GL_STATIC_DRAW));
        
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
        
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]));
        GLCall(glBufferData(GL_ARRAY_BUFFER,
                     numVertices * sizeof(texCoords[0]),
                     &texCoords[0],
                     GL_STATIC_DRAW));
        
        GLCall(glEnableVertexAttribArray(1));
        GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0));
        
        GLCall(glBindVertexArray(0));
        
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(2, m_vertexArrayBuffers);
        glDeleteVertexArrays(1, &m_vertexArrayObject);
    }

#else // Donovan Greene (youtube poster) implementation.
      // https://www.youtube.com/watch?v=17axYo6mKhY&lc=UgiMnSfX381MA3gCoAEC

    Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
    {
        m_drawCount = numVertices;
        GLCall(glGenVertexArrays(1, &m_vertexArrayObject));
        GLCall(glBindVertexArray(m_vertexArrayObject));
        
        GLCall(glGenBuffers(1, &m_vertexArrayBuffer));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer));
        GLCall(glBufferData(GL_ARRAY_BUFFER,
                            numVertices * sizeof(Vertex),
                            vertices,
                            GL_STATIC_DRAW));
        
        // schema for position data
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0));
        
        // schema for texture coordinate data
        GLCall(glEnableVertexAttribArray(1));
        void * texcoordOffset = (void *)(3 * sizeof(float));
        GLCall(glVertexAttribPointer(1,
                                     2,
                                     GL_FLOAT,
                                     GL_FALSE,
                                     sizeof(Vertex),
                                     texcoordOffset));
        
        GLCall(glBindVertexArray(0));
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &m_vertexArrayBuffer);
        glDeleteVertexArrays(1, &m_vertexArrayObject);
    }
#endif

void Mesh::Draw()
{
    GLCall(glBindVertexArray(m_vertexArrayObject));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, m_drawCount));
    GLCall(glBindVertexArray(0));
}
