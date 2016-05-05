#include "application.h"

#include <SDL.h>
#include <exception>

int main(int argc, char* argv[]){
    SDL_Window* wnd;
    SDL_Renderer* renderer;
    Application* app;

    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0){
        SDL_LogCritical(
                    SDL_LOG_CATEGORY_APPLICATION,
                    "Can't init Audio|Video: %s",
                    SDL_GetError());
        SDL_Quit();
        return 1;
    }

    try{
        app = new Application();
        app->exec();
    } catch(std::exception& e) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,"An error occured: %s", e.what());
    }
    delete app;
    SDL_Quit();
}
