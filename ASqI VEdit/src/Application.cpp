#include "Application.h"

#include <SDL_image.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <iostream>

#include "DraggableNode.h"

Application::Application() {
    if (!init()) {
        (void)fprintf(stderr, "Initialization failed, aborting!\n");
    }

    initViewportUI();
    initBottomPanelUI();
    initSidePanelUI();
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
    m_window = SDL_CreateWindow(
        "A²ᵢ VEdit",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windWidth, m_windHeight,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE
        );
    
    if (!m_window) {
        (void)fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        return false;
    }

    // Set window icon
    SDL_Surface* icon = IMG_Load("./assets/win_tree_big.ico");
    SDL_SetWindowIcon(m_window, icon);

    // Smallest allowable window size
    SDL_SetWindowMinimumSize(m_window, 800, 480);

    // Initialize SDL renderer
    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if (!m_renderer) {
        (void)fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        return false;
    }

     // Initialize ImGui
    IMGUI_CHECKVERSION();
    m_context = ImGui::CreateContext();
    ImGui::SetCurrentContext(m_context);

    // Initialize ImGui for SDL and OpenGL
    ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer2_Init(m_renderer);

    // Setup IO and load fonts
    m_io = &ImGui::GetIO();
    ImFont* mainFont = m_io->Fonts->AddFontFromFileTTF("assets/fonts/NeoSansProLight.OTF", 24.0f);
    m_io->FontDefault = mainFont;

    // Setup custom window style
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.17647058823529413f, 0.16470588235294117f, 0.1803921568627451f, 1.0f);
    
    // Initialize layout, size references, and drag targets
    m_mainViewport = new MainViewport(m_renderer);
    m_mainViewport->registerSize(&m_windWidth, &m_windHeight);
    m_mainViewport->setDragTarget(&m_dragTarget);
    
    m_sidePanel = new SidePanel(m_renderer);
    m_sidePanel->registerSize(&m_windWidth, &m_windHeight);
    m_sidePanel->setDragTarget(&m_dragTarget);
    
    m_bottomPanel = new BottomPanel(m_renderer);
    m_bottomPanel->registerSize(&m_windWidth, &m_windHeight);
    
    return true;
}


/**
 * \brief Kills the main process and exits the application
 */
void Application::kill() const {
    SDL_DestroyRenderer( m_renderer );
    SDL_DestroyWindow( m_window );
    SDL_Quit();
    exit(1);
}

void Application::run() {
    bool running = true;
    SDL_Event event;

    // Main application loop
    while (running) {
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Event polling and handling
        while (SDL_PollEvent(&event) != 0) {
            ImGui_ImplSDL2_ProcessEvent(&event);

            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                // Update window size references and call resize on layout elements
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        m_windWidth = event.window.data1;
                        m_windHeight = event.window.data2;
                        
                        m_mainViewport->resize();
                        m_sidePanel->resize();
                        m_bottomPanel->resize();
                    }                
                default:
                    break;
            }
        }

        int width, height;
        SDL_GetWindowSize(m_window, &width, &height);
        m_io->DisplaySize = ImVec2((float)width, (float)height);

        // Clear screen
        SDL_SetRenderDrawColor(m_renderer, 42, 42, 42, 255);
        SDL_RenderClear(m_renderer);

        // Layout rendering
        m_mainViewport->draw();
        m_sidePanel->draw();
        m_bottomPanel->draw();

        // Render ImGui Elements
        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer);

        // Present final image
        SDL_RenderPresent(m_renderer);
    }

    // Cleanup ImGui resources
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    kill();
}

void Application::initViewportUI() {
    
}

void Application::initBottomPanelUI() {
    SDL_Surface* nodeIcon = IMG_Load("assets/win_tree.ico");
    m_bottomPanel->add("TestNode", new DraggableNode(nodeIcon, { 20, 20 }));
}

void Application::initSidePanelUI() {
    
}


