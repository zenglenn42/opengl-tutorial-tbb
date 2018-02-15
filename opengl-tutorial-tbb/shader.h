//
//  shader.h
//  opengl-tutorial-tbb
//

#ifndef SHADER_H
#define SHADER_H

#include "transform.h"
#include <string>
#include <GL/glew.h>

class Shader {
public:
    Shader(const std::string& fileName);
    
    void Bind();
    void Update(const Transform& transform);
    
    virtual ~Shader();
    
protected:
private:
    static const unsigned int NUM_SHADERS = 2;
    Shader(const Shader& shader) {}
    void operator=(const Shader& shader) {}
    
    std::string LoadShader(const std::string& fileName);
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    GLuint CreateShader(const std::string& text, unsigned int type);

    enum {
        TRANSFORM_U,
        NUM_UNIFORMS
    };
    
    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
};

#endif /* SHADER_H */
