//
//  glerror.h
//  opengl-tutorial-tbb
//

#ifndef glerror_h
#define glerror_h

#include <debugbreak/debugbreak.h>

#define ASSERT(x) if (!(x)) debug_break()
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif /* glerror_h */
