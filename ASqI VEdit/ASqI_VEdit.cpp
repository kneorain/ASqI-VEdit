#include <SDL.h>
#include "Application.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    
    Application app = Application();
    app.run();

    return 0;
}
