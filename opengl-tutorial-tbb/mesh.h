//
//  mesh.h
//  opengl-tutorial-tbb
//

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "obj_loader.h"

// See: Tutorial implementation. See: https://youtu.be/17axYo6mKhY
#define TUTORIAL_IMPLEMENTATION

#ifdef TUTORIAL_IMPLEMENTATION
    class Vertex
    {
    public:
        Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 0))
        {
            this->pos = pos;
            this->texCoord = texCoord;
            this->normal = normal;
        }
        
        inline glm::vec3* GetPos() { return &pos; }
        inline glm::vec2* GetTexCoord() { return &texCoord; }
        inline glm::vec3* GetNormal() { return &normal; }
        
    protected:
    private:
        glm::vec3 pos;
        glm::vec2 texCoord;
        glm::vec3 normal;
    };

    class Mesh
    {
    public:
        Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
        Mesh(const std::string& filename);
        
        void Draw();
        
        virtual ~Mesh();
    private:
        Mesh(const Mesh& other);
        void operator=(const Mesh& other);
        
        void InitMesh(const IndexedModel& model);
        
        enum
        {
            POSITION_VB,
            TEXCOORD_VB,
            NORMAL_VB,
            INDEX_VB,
            NUM_BUFFERS
        };
        GLuint m_vertexArrayObject;
        GLuint m_vertexArrayBuffers[NUM_BUFFERS];
        unsigned int m_drawCount;
    };

#else  // Donovan Greene (youtube poster) implementation.
       // https://www.youtube.com/watch?v=17axYo6mKhY&lc=UgiMnSfX381MA3gCoAEC

    struct Vertex
    {
        Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
        {
            this->pos = pos;
            this->texCoord = texCoord;
        }
        glm::vec3 pos;
        glm::vec2 texCoord;
    };

    class Mesh
    {
    public:
        Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
        void Draw();
        ~Mesh();
    private:
        GLuint m_vertexArrayObject;
        GLuint m_vertexArrayBuffer[2];
        unsigned int m_drawCount;
    };

#endif

#endif // MESH_H
