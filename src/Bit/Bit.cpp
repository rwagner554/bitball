#include <Bit/Bit.h>

Bit::Bit()
{
    bool sLib = this->InitLibraries();

    if (!sLib) {
        std::cout << "[-] Failed Initalizing Libraries.\n";
        return;
    }

    bool sWin = this->InitWindow();

    if (!sWin) {
        std::cout << "[-] Failed Initalizing Window.\n";
        return;
    }
}

Bit::~Bit()
{
    SDL_DestroyWindow(this->kWindow);
    SDL_Quit();
}

void Bit::Loop()
{
    while (!this->kWindowShouldClose) {
        // Input
        SDL_PollEvent(&this->kWindowEvents);

        if (this->kWindowEvents.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            this->kWindowShouldClose = true;
        }

        // Update

        // Render
    }
}

// Init SDL3.
bool Bit::InitLibraries()
{
    bool didSucceed = true;

    // init SDL and check for errors
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        didSucceed = false;
        return didSucceed;
    }

    return didSucceed;
}

bool Bit::InitWindow()
{
    // create window and check for errors
    this->kWindow = SDL_CreateWindow(
        "BitBall",
        640,
        480,
        SDL_WINDOW_OPENGL
    );

    if (this->kWindow == NULL) {
        return false;
    } 
    
    return true;
}
