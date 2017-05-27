#ifndef WINDOW_H
#define WINDOW_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

#ifdef _WIN32
	#include <GL/glew.h>
#endif

#include "Keyboard.h"

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
    inline KeyboardState getKeyboardState() { return SDL_GetKeyboardState(NULL); }
};

#endif
