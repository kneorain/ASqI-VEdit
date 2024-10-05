#ifndef _TYPES_H
#define _TYPES_H

#include <algorithm>
#include <cstdio>
#include <SDL_surface.h>
#include <imgui.h>
#include <SDL_image.h>
#include <string>

struct IntVec2 {
    int x, y;
};

enum FontStyleType {
    BLACK,
    BLACK_ITALIC,
    BOLD,
    BOLD_ITALIC,
    ITALIC,
    LIGHT,
    LIGHT_ITALIC,
    MEDIUM,
    MEDIUM_ITALIC,
    REGULAR,
    ULTRA,
    ULTRA_ITALIC
};

const std::string FontStyles[] = {
    "Black", "BlackIt", "Bold", "BoldIt", "Italic",
    "Light", "LightIt", "Medium", "MedIt", "Regular",
    "Ultra", "UltIt"
};

static SDL_Texture* loadTextureFromFile(SDL_Renderer* renderer, const char* filename) {
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        (void)fprintf(stderr, "Failed to load texture '%s': %s", filename, IMG_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

inline ImFont* loadFont(float size = 16.0, FontStyleType style = LIGHT) {
    return ImGui::GetIO().Fonts->AddFontFromFileTTF(
        ("assets/fonts/NeoSansPro" + FontStyles[style] + ".OTF").c_str(), size
        );
}

inline int clamp(int n, int lower, int upper) {
    return std::max(lower, std::min(n, upper));
}

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