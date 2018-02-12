//
//  glerror.cpp
//
//  See gldebug.h for usage and attribution credits.
//

#include <GL/glew.h>
#include <iostream>

void GLClearError() {
    
    // Get to an empty error state, typically before a call to
    // an OpenGL primitive.
    
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cerr << "[OpenGL Error] (" << error << ") " << function << " " << file << " " << line << std::endl;
        return false;
    }
    return true;
}
