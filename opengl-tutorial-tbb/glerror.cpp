//
//  glerror.cpp
//  opengl-tutorial-tbb
//
//  Courtesy: https://www.youtube.com/watch?v=FBbPWSOQ0-w&index=10&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
//

#include <GL/glew.h>
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cerr << "[OpenGL Error] (" << error << ") " << function << " " << file << " " << line << std::endl;
        return false;
    }
    return true;
}
