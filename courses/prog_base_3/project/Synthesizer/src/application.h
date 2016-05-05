#ifndef APPLICATION_H
#define APPLICATION_H

#include "audiogenerator.h"
#include <SDL.h>

class Application
{
public:
    Application();
    ~Application();
    void exec();
private:
    void draw_interface();

    SDL_Window* wnd;
    SDL_Renderer* renderer;
    AudioGenerator* generator;
};

#endif // APPLICATION_H
