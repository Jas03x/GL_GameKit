#include "Window.h"

Window::Window(const char* title, unsigned int width, unsigned int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL initalization error:\n%s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        printf("SDL window creation error:\n%s\n", SDL_GetError());
        return -1;
    }

    this->context = SDL_GL_CreateContext(this->window);
    if(context == NULL) {
        printf("SDL OpenGL context creation error:\n%s\n", SDL_GetError());
        return -1;
    }
}

Window::~Window()
{
    SDL_GL_DeleteContext(this->context);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
