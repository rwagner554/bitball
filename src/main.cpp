#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>



int main(int argc, char* argv[]) {
    
    // init SDL and check for errors
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "[-] SDL_INIT failed: " << SDL_GetError() << '\n';
    }

    // create window and check for errors
    SDL_Window *window = SDL_CreateWindow(
        "BitBall",
        640,
        480,
        SDL_WINDOW_OPENGL
    );
    // render loop
    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // close window and clean up SDL
    return 0;
}