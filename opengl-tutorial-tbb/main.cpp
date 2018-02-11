//
//  main.cpp
//  opengl-tutorial-tbb
//

#include <iostream>
#include "display.h"

int main(int argc, const char * argv[]) {
    Display display(800, 600, "Hello World");
    while (!display.IsClosed()) {
        display.Clear(0.2f, 0.3f, 0.8f, 1.0f);
        display.Update();
    }
    return 0;
}
