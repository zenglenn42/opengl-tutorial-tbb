//
//  mesh.h
//  opengl-tutorial-tbb
//

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

// See: Tutorial implementation. See: https://youtu.be/17axYo6mKhY

#ifdef TUTORIAL_IMPLEMENTATION
    class Vertex
    {
    public:
        Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
        {
            this->pos = pos;
            this->texCoord = texCoord;
        }
        
        inline glm::vec3* GetPos() { return &pos; }
        inline glm::vec2* GetTexCoord() { return &texCoord; }
        
    protected:
    private:
        glm::vec3 pos;
        glm::vec2 texCoord;
    };

    class Mesh
    {
    public:
        Mesh(Vertex * vertices, unsigned int numVertices);
        
        void Draw();
        
        virtual ~Mesh();
    private:
        Mesh(const Mesh& other);
        void operator=(const Mesh& other);
        
        enum
        {
            POSITION_VB,
            TEXCOORD_VB,
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
        Mesh(Vertex * verts, unsigned int numVertices);
        void Draw();
        ~Mesh();
    private:
        GLuint m_vertexArrayObject;
        GLuint m_vertexArrayBuffer;
        unsigned int m_drawCount;
    };

#endif

#endif // MESH_H
