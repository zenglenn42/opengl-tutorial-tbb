//
//  texture.cpp
//  opengl-tutorial-tbb
//

#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <cassert>
#include <iostream>
#include "gldebug.h"

Texture::Texture(const std::string& filename)
{
    int width, height, numChannels;
    int desiredChannels = 4;
    unsigned char* imageData = stbi_load(filename.c_str(),
                                         &width,
                                         &height,
                                         &numChannels,
                                         desiredChannels);
    
    if (imageData == nullptr)
        std::cerr << "Texture loaoding failed for texture: " << filename << std::endl;
    
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Send texture data to GPU.
    
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 width,
                 height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 imageData);
    
    stbi_image_free(imageData);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int texId)
{
    assert(texId >= 0 && texId <= 31);
    glActiveTexture(GL_TEXTURE0 + texId);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
