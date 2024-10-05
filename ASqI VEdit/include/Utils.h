#ifndef _TYPES_H
#define _TYPES_H

#include <cstdio>
#include <SDL_surface.h>

struct IntVec2 {
    int x, y;
};

static SDL_Surface* resizeSurface(SDL_Surface* originalSurface, int width, int height) {
    SDL_Surface* newSurface = SDL_CreateRGBSurface(
        0, width, height,
        originalSurface->format->BitsPerPixel,
        originalSurface->format->Rmask,
        originalSurface->format->Gmask,
        originalSurface->format->Bmask,
        originalSurface->format->Amask
    );

    if (newSurface == nullptr) {
        (void)fprintf(stderr, "Failed to create surface (%dx%d): %s\n", width, height, SDL_GetError());
    }

    SDL_Rect destRect = { 0, 0, width, height };
    SDL_BlitScaled(originalSurface, NULL, newSurface, &destRect);

    return newSurface;
}

inline SDL_Surface* resizeSurface(SDL_Surface* originalSurface, IntVec2 size) {
    return resizeSurface(originalSurface, size.x, size.y);
}

#endif