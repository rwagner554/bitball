#ifndef _BIT_H

#include <SDL3/SDL.h>

#include <iostream>

class Bit {
public:
Bit();
~Bit();

void Loop();
private:
SDL_Window* kWindow = nullptr;
SDL_Event kWindowEvents{};
bool kWindowShouldClose = false;

bool InitLibraries();
bool InitWindow();
};

#endif