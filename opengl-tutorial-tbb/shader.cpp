//
//  shader.cpp
//  opengl-tutorial-tbb
//

#include "shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& fileName) {
    m_program = glCreateProgram();
    m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);
    
    for(unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);
    
    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");
    
    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

}

Shader::~Shader()
{
    for (unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_program);
}

void Shader::Bind()
{
    glUseProgram(m_program);
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
    GLuint shader = glCreateShader(type);
    
    if(shader == 0)
        std::cerr << "Error compiling shader type " << type << std::endl;
    
    const GLchar* p[1];
    p[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = text.length();
    
    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader);
    
    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");
    
    return shader;
}

std::string Shader::LoadShader(const std::string& fileName) {
    std::ifstream file;
    file.open((fileName).c_str());
    
    std::string output;
    std::string line;
    
    if (file.is_open()) {
        while (file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    } else {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }
    
    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
    GLint success = 0;
    GLchar error[1024] = { 0 };
    
    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);
    
    if (success == GL_FALSE) {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
