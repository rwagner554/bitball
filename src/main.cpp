#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>



int main(int argc, char* argv[]) {
    constexpr int kScreenWidth{ 640 };
    constexpr int kScreenHeight{ 480 };

    // init SDL and check for errors
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "[-] SDL_INIT failed: " << SDL_GetError() << '\n';
    }

    // create window and check for errors

    // render loop


    // close window and clean up SDL
    return 0;
}