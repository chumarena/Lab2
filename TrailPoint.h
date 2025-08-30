#include <SDL2/SDL.h>
#include <iostream>
#include "Vector2D.cpp"


struct TrailPoint {
    Vector2D position;
    float radius;
    Uint8 alpha;// unsigned int 8 - количество нужных битов
    Uint32 creationTime;
};