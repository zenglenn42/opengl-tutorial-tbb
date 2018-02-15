//
//  texture.h
//  opengl-tutorial-tbb
//

#ifndef texture_h
#define texture_h

#include <string>
#include <GL/glew.h>

class Texture {
public:
    Texture(const std::string& filename);

    void Bind(unsigned int texId);
    
    virtual ~Texture();
protected:
private:
    Texture(const Texture& other) {}
    void operator=(const Texture& rhs) {}
    
    GLuint m_texture;   // Handle for texture returned by OpenGL
};

#endif // texture_h
