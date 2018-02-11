//
//  display.h
//  opengl-tutorial-tbb
//
//  Created by m on 2/11/18.
//  Copyright © 2018 zenglenn42. All rights reserved.
//

#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
    Display(int width, int height, const std::string& title);
    
    void Clear(float r, float g, float b, float a);
    void SwapBuffers();
    
    virtual ~Display();
protected:
private:
    void operator=(const Display& display) {}
    Display(const Display& display) {}
    
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
};

#endif
