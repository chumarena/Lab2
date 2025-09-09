// CircleRenderer.h
#pragma once
#include <SDL2/SDL.h>
#include "Vector2D.h"

class CircleRenderer {
public:
    static void render(SDL_Renderer* renderer, const Vector2D& center, 
                      int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};