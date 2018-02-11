//
//  main.cpp
//  opengl-tutorial-tbb
//

#include <iostream>
#include "display.h"

int main(int argc, const char * argv[]) {
    Display display(800, 600, "Hello World");

    bool quit = false;
    SDL_Event event;
    
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
    return 0;
}
