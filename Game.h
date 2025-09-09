// Game.h
#pragma once
#include "Vector2D.h"
#include "TrailPoint.h"
#include "CircleRenderer.h"
#include <SDL2/SDL.h>
#include <vector>

class Game {
private:
    static const int WIDTH = 800;
    static const int HEIGHT = 600;
    static const float SPEED;
    static const Uint32 TRAIL_DELAY;
    static const float MAX_RADIUS;
    static const int TRAIL_DURATION;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    Vector2D position;
    Vector2D velocity;
    std::vector<TrailPoint> trail;
    
    bool upPressed;
    bool downPressed;
    bool leftPressed;
    bool rightPressed;
    Uint32 lastTrailTime;
    
    bool initializeSDL();
    void processEvents(bool& running);
    void update(Uint32 currentTime);
    void render();
    void cleanUp();

public:
    Game();
    ~Game();
    void run();
};