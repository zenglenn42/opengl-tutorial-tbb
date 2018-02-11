//
//  main.cpp
//  opengl-tutorial-tbb
//
//  Copyright © 2018 zenglenn42. All rights reserved.
//

#include <iostream>
#include "display.h"

int main(int argc, const char * argv[]) {
    //Display display(800, 600, "Hello World");

    bool quit = false;
    SDL_Event event;
    
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window * screen = SDL_CreateWindow("My SDL Empty Window",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    
    while (!quit)
    {
        SDL_WaitEvent(&event);
        
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
    
    SDL_Quit();
    return 0;
}
