//
//  gldebug.h
//
//  Include this header in code where you want glError automatically
//  checked by wrappering OpenGL primitives with GLCall( ).
//
//  An error condition will break to the debugger and display on the
//  console the error code, source file, and line number for the
//  offending OpenGL function.
//
//  Usage:
//
//     GLCall(glSomeOpenGLFunction());
//
//  Example:
//
//     #define GLDEBUG
//     #include "gldebug.h"
//     ..
//     GLCall(glGenVertexArrays(1, &m_vertexArrayObject));
//
//  Limits:
//
//     Doesn't seem to work well with wrappering glBegin() and glEnd().
//
//  Courtesy:
//
//     Yan Cherno
//     https://www.youtube.com/watch?v=FBbPWSOQ0-w&index=10&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
//
//     Scott Tsai
//     https://github.com/scottt/debugbreak
//     Provides cross-platform debug_break support for gcc, clang, and msvc.
//

#ifndef gldebug_h
#define gldebug_h

#include <debugbreak/debugbreak.h>

#ifdef GLDEBUG

#define ASSERT(x) if (!(x)) debug_break()
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#else

#define GLCall(x) x

#endif

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif // gldebug_h
