// CircleRenderer.cpp
#include "CircleRenderer.h"
#include <cmath>

void CircleRenderer::render(SDL_Renderer* renderer, const Vector2D& center, 
                           int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    
    for (int dy = -radius; dy <= radius; dy++) {
        int dx = static_cast<int>(std::sqrt(radius * radius - dy * dy));
        SDL_RenderDrawLine(renderer, 
                          static_cast<int>(center.getX()) - dx, 
                          static_cast<int>(center.getY()) + dy, 
                          static_cast<int>(center.getX()) + dx, 
                          static_cast<int>(center.getY()) + dy);
    }
}