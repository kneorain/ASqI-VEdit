#include "Application.h"

#include <SDL_image.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <iostream>

Application::Application() {
    if (!init()) {
        (void)fprintf(stderr, "Initialization failed, aborting!\n");
    }
}


/**
 * \brief Initializes SDL's resources
 * \return Whether the initialization succeeded
 */
bool Application::init() {
    // Initialize SDL
    if (SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
        (void)fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    } 

    // Create SDL window
    window = SDL_CreateWindow( "A²ᵢ VEdit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600, SDL_WINDOW_SHOWN );
    if (!window) {
        (void)fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        return false;
    }

    // Set window icon
    SDL_Surface* icon = IMG_Load("./assets/win_tree_big.ico");
    SDL_SetWindowIcon(window, icon);

    // Initialize SDL renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if (!renderer) {
        (void)fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        return false;
    }

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    context = ImGui::CreateContext();
    ImGui::SetCurrentContext(context);

    // Initialize ImGui for SDL and OpenGL
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    // Setup ImGui with SDL and style
    io = &ImGui::GetIO();
    ImGui::StyleColorsDark();
    
    // Initialize the layout
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

void Application::run() {
    bool running = true;
    SDL_Event event;

    while (running) {
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        
        while (SDL_PollEvent(&event) != 0) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        int width, height;
        SDL_GetWindowSize(window, &width, &height);
        io->DisplaySize = ImVec2((float)width, (float)height);

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 42, 42, 42, 255);
        SDL_RenderClear(renderer);

        // Main layout displays
        mainViewport->draw();
        sidePanel->draw();
        bottomPanel->draw();

        // Temporary ImGui rendering, to be moved into the classes
        ImGui::Begin("Control Panel");
        ImGui::Text("Hello, ImGui!");
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

        // Present final image
        SDL_RenderPresent(renderer);
    }

    // Cleanup ImGui resources
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    kill();
}