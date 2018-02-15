//
//  display.h
//  opengl-tutorial-tbb
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Display
{
public:
    Display(int width, int height, const std::string& title);
    void Update();
    bool IsClosed();
    void Clear(float r, float g, float b, float a);
    void Clear(const glm::vec4 &color);
    void SwapBuffers();
    
    virtual ~Display();
protected:
private:
    void operator=(const Display& display) {}
    Display(const Display& display) {}
    
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    bool m_isClosed;
};

#endif
