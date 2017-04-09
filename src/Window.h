#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window
{
private:
    SDL_Window* window;
    SDL_GLContext context;

public:
    Window(const char* title, unsigned int width, unsigned int height);
    ~Window();
    inline void swap_buffers(){ SDL_GL_SwapWindow(this->window); }
    inline int poll(SDL_Event& event) { return SDL_PollEvent(&event); }
};

#endif
