#include <Bit/Bit.h>

Bit::Bit()
{
    bool sLib = this->InitLibraries();

    if (!sLib) {
        std::cout << "[-] Failed Initalizing Libraries.\n";
        return;
    }

    // bool sWin = this->InitWindow();

    // if (!sWin) {
    //     std::cout << "[-] Failed Initalizing Window.\n";
    //     return;
    // }
}

Bit::~Bit()
{
    SDL_GL_DestroyContext(this->kContext);
    SDL_DestroyWindow(this->kWindow);
    SDL_Quit();
}

void Bit::Loop()
{
    this->kDeltaTime = 0.1f;
    while (!this->kWindowShouldClose) {
        // Input
        SDL_PollEvent(&this->kWindowEvents);

        if (this->kWindowEvents.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            this->kWindowShouldClose = true;
        }

        // Update
        this->color += 0.1f;
        if (this->color >= 1.0f) {
            this->color = 0.0f;
        }

        glClearColor(color * this->kDeltaTime, color * this->kDeltaTime, color * this->kDeltaTime, 1.0f);

        // Render
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(this->kWindow);
    }
}

// Init SDL3.
bool Bit::InitLibraries()
{

    // init SDL and check for errors
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return false;
    } else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    }

    // create window and check for errors
    this->InitWindow();

    this->kContext = SDL_GL_CreateContext(this->kWindow);
    if (this->kContext == NULL) {
        std::cout << "[-] Failed Creating OpenGL Context.\n";
        return false;
    }

    // Init glad.
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "[-] Failed Loading OpenGL Functions.\n";
        return false;
    } else {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    }

    return true;
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
        std::cout << "[-] Failed Creating Window.\n";
        return false;
    } else {
        SDL_GL_SetSwapInterval(1);
    }
    
    return true;
}
