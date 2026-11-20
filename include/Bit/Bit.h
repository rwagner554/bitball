#ifndef _BIT_H

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <iostream>

class Bit {
public:
Bit();
~Bit();

void Loop();
private:
SDL_Window* kWindow = nullptr;
SDL_GLContext kContext{};
SDL_Event kWindowEvents{};
bool kWindowShouldClose = false;

GLfloat color = 0.0f;
float kDeltaTime = 0.0f;

bool InitLibraries();
bool InitWindow();
};

#endif