//
//  mesh.cpp
//  opengl-tutorial-tbb
//

#include "mesh.h"
#include "gldebug.h"
#include <vector>

Mesh::Mesh(const std::string& filename)
{
    IndexedModel model = OBJModel(filename).ToIndexedModel();
    InitMesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
    IndexedModel model;
    
    for (unsigned int i = 0; i < numVertices; i++)
    {
        model.positions.push_back(*vertices[i].GetPos());
        model.texCoords.push_back(*vertices[i].GetTexCoord());
        model.normals.push_back(*vertices[i].GetNormal());
    }
    
    for (unsigned int i = 0; i < numIndices; i++)
    {
        model.indices.push_back(indices[i]);
    }
    
    InitMesh(model);
}

void Mesh::InitMesh(const IndexedModel& model)
{
    m_drawCount = model.indices.size();
    
    GLCall(glGenVertexArrays(1, &m_vertexArrayObject));
    GLCall(glBindVertexArray(m_vertexArrayObject));
    
    GLCall(glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers));
    
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]));
    GLCall(glBufferData(GL_ARRAY_BUFFER,
                        model.positions.size() * sizeof(model.positions[0]),
                        &model.positions[0],
                        GL_STATIC_DRAW));
    
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]));
    GLCall(glBufferData(GL_ARRAY_BUFFER,
                        model.positions.size() * sizeof(model.texCoords[0]),
                        &model.texCoords[0],
                        GL_STATIC_DRAW));
    
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0));
    
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]));
    GLCall(glBufferData(GL_ARRAY_BUFFER,
                        model.normals.size() * sizeof(model.normals[0]),
                        &model.normals[0],
                        GL_STATIC_DRAW));
    
    GLCall(glEnableVertexAttribArray(2));
    GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0));
    
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                        model.indices.size() * sizeof(model.indices[0]),
                        &model.indices[0],
                        GL_STATIC_DRAW));
    
    GLCall(glBindVertexArray(0));
}

Mesh::~Mesh()
{
    glDeleteBuffers(2, m_vertexArrayBuffers);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
    GLCall(glBindVertexArray(m_vertexArrayObject));
    GLCall(glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0));
    GLCall(glBindVertexArray(0));
}
