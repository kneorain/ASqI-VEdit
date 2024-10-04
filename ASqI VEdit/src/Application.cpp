#include "Application.h"

#include <SDL_image.h>
#include <iostream>

/**
 * \brief Initializes SDL's resources
 * \return Whether the initialization succeeded
 */
bool Application::init() {
    if (SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        system("pause");
        return false;
    } 

    window = SDL_CreateWindow( "A²ᵢ VEdit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600, SDL_WINDOW_SHOWN );
    if (!window) {
        std::cout << "Error creating window: " << SDL_GetError()  << std::endl;
        system("pause");
        return false;
    }

    SDL_Surface* icon = IMG_Load("./assets/win_tree_big.ico");
    SDL_SetWindowIcon(window, icon);

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if (!renderer) {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    mainViewport = new MainViewport(renderer);
    sidePanel = new SidePanel(renderer);
    bottomPanel = new BottomPanel(renderer);
    
    return true;
}


/**
 * \brief Kills the main process and exits the application
 */
void Application::kill() {
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
    exit(1);
}

/**
 * \brief The main draw loop for the application
 */
bool Application::loop() {
    static const unsigned char* keys = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    SDL_SetRenderDrawColor(renderer, 45, 42, 46, 255);
    SDL_RenderClear(renderer);

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT:
            return false;
        }
    }
    
    // Render window sections
    
    SDL_RenderPresent( renderer );
    
    return true;
}

void Application::run() {
    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 42, 42, 42, 255);
        SDL_RenderClear(renderer);

        mainViewport->draw();
        sidePanel->draw();
        bottomPanel->draw();

        SDL_RenderPresent(renderer);
    }

    kill();
}