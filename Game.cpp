// Game.cpp
#include "Game.h"
#include <iostream>
#include <algorithm>

const float Game::SPEED = 2.0f;
const Uint32 Game::TRAIL_DELAY = 100;
const float Game::MAX_RADIUS = 20.0f;
const int Game::TRAIL_DURATION = 1500;

Game::Game() : window(nullptr), renderer(nullptr),
               position(WIDTH / 2, HEIGHT / 2),
               upPressed(false), downPressed(false),
               leftPressed(false), rightPressed(false),
               lastTrailTime(0) {}

Game::~Game() {
    cleanUp();
}

bool Game::initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow("Moving Point with Trail", 
                             SDL_WINDOWPOS_CENTERED, 
                             SDL_WINDOWPOS_CENTERED, 
                             WIDTH, HEIGHT, 
                             SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 
                                 SDL_RENDERER_ACCELERATED | 
                                 SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    return true;
}

void Game::processEvents(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP: upPressed = true; break;
                case SDLK_DOWN: downPressed = true; break;
                case SDLK_LEFT: leftPressed = true; break;
                case SDLK_RIGHT: rightPressed = true; break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_UP: upPressed = false; break;
                case SDLK_DOWN: downPressed = false; break;
                case SDLK_LEFT: leftPressed = false; break;
                case SDLK_RIGHT: rightPressed = false; break;
            }
        }
    }
}

void Game::update(Uint32 currentTime) {
    velocity = Vector2D(0, 0);
    if (upPressed) velocity += Vector2D(0, -SPEED);
    if (downPressed) velocity += Vector2D(0, SPEED);
    if (leftPressed) velocity += Vector2D(-SPEED, 0);
    if (rightPressed) velocity += Vector2D(SPEED, 0);

    position += velocity;
    position.setPosition(position.getX(), position.getY(), 5.0f, WIDTH - 5.0f, 5.0f, HEIGHT - 5.0f);

    bool isMoving = !velocity.isZero();
    
    if (isMoving && currentTime - lastTrailTime > TRAIL_DELAY) {
        trail.emplace_back(position, 3.0f, 100, currentTime);
        lastTrailTime = currentTime;
    }

    // Remove expired trail points
    trail.erase(std::remove_if(trail.begin(), trail.end(),
        [currentTime](const TrailPoint& point) {
            float age = currentTime - point.getCreationTime();
            return age > TRAIL_DURATION;
        }), trail.end());

    // Update remaining trail points
    for (auto& point : trail) {
        float age = currentTime - point.getCreationTime();
        float lifeRatio = age / TRAIL_DURATION;
        point.update(lifeRatio, MAX_RADIUS);
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render trail
    for (const auto& point : trail) {
        CircleRenderer::render(renderer, point.getPosition(), 
                             static_cast<int>(point.getRadius()),
                             200, 200, 200, point.getAlpha());
    }

    // Render main point
    CircleRenderer::render(renderer, position, 5, 255, 255, 255, 255);

    SDL_RenderPresent(renderer);
}

void Game::cleanUp() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Game::run() {
    if (!initializeSDL()) {
        return;
    }
    
    bool running = true;
    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        
        processEvents(running);
        update(currentTime);
        render();
        
        SDL_Delay(10);
    }
}