#include "application.h"
#include <stdexcept>

#define WND_HEIGHT 500
#define WND_WIDTH 500

void Application::draw_interface(){
    //Draw white background
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Application::exec(){
    SDL_Event ev;
    while(true){
        draw_interface();
        while(SDL_PollEvent(&ev)){
            if(ev.type==SDL_QUIT)
                return;
        }
    }
}

Application::Application()
{
    if(SDL_CreateWindowAndRenderer(WND_WIDTH, WND_HEIGHT, SDL_WINDOW_SHOWN, &wnd, &renderer)!=0){
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Can't create SDL renderer: %s",
                        SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }

    generator = new AudioGenerator();
}

Application::~Application(){
    delete generator;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(wnd);
}
