#include <SDL.h>
#include <SDL_syswm.h>

#include "Application.h"

int main(int argc, char* argv[]) {
    // Allow DPI aware rendering
    SetProcessDPIAware();
    
    Application app = Application();
    app.run();

    return 0;
}
