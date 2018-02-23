//
// This is the hello.cpp example program from the SDL2-widgets
// package.  I've dragged it here temporarily to test that I 
// can build it within my Xcode project environment.
//
// This is my starting point for enhancing the OpenGL tutorial 
// program with some SDL-friendly user-interface elements.
//

#if defined(BUILD_SDL2_WIDGET_EXAMPLE)

#include <SDL2/SDL_widgets.h>

TopWin *top_win;
Button *but;

int main(int,char**) {
  top_win=new TopWin("Hello",Rect(100,100,120,100),0,0,false,
    []() {
      top_win->clear();
      draw_title_ttf->draw_string(top_win->render,"Hello world!",Point(20,40));
    }
  );
  but=new Button(top_win,0,Rect(5,10,60,0),"catch me",
    [](Button *b) {
      static int dy=60;
      b->hide();
      b->move(0,dy);
      b->hidden=false;
      dy= dy==60 ? -60 : 60;
    });
  get_events();
  return 0;
}

#endif
