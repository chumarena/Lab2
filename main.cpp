#include "Draw.cpp"



int main(int argc, char* argv[]) {
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Ошибка инициализации SDL: %s", SDL_GetError());
        return 1;
    }

    
    const int WIDTH = 800;
    const int HEIGHT = 600;
    SDL_Window* window = SDL_CreateWindow("Движение точки с следом", 
                                         SDL_WINDOWPOS_CENTERED, 
                                         SDL_WINDOWPOS_CENTERED, 
                                         WIDTH, HEIGHT, 
                                         SDL_WINDOW_SHOWN);
    
    if (!window) {
        SDL_Log("Ошибка создания окна: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
                                               SDL_RENDERER_ACCELERATED | 
                                               SDL_RENDERER_PRESENTVSYNC);
    
    if (!renderer) {
        SDL_Log("Ошибка создания рендерера: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    
    Vector2D position(WIDTH / 2, HEIGHT / 2);
    Vector2D velocity(0, 0);
     float SPEED = 2.0f;

    
    std::vector<TrailPoint> trail;
    const Uint32 TRAIL_DELAY = 100;
    Uint32 lastTrailTime = 0;
    const float MAX_RADIUS = 20.0f;
    const int TRAIL_DURATION = 1500;
    
    
    bool isMoving = false;

    
    bool upPressed = false;
    bool downPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;

    
    bool running = true;
    SDL_Event event;
    
    
    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        

        
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

        
        velocity = Vector2D(0, 0);
        if (upPressed) velocity += Vector2D(0, -SPEED);
        if (downPressed) velocity += Vector2D(0, SPEED);
        if (leftPressed) velocity += Vector2D(-SPEED, 0);
        if (rightPressed) velocity += Vector2D(SPEED, 0);

        
        position += velocity;
        
        
        
        
        
        position.setPosition(position.getX(), position.getY(), 5.0f, WIDTH - 5.0f, 5.0f, HEIGHT - 5.0f);

        
        isMoving = !velocity.isZero();
        
       
        if (isMoving && currentTime - lastTrailTime > TRAIL_DELAY) { // Добавление нового следа только если точка движется для того чтобы при остановке не появлялись следы
            TrailPoint newPoint;
            newPoint.position = position;
            newPoint.radius = 3.0f;
            newPoint.alpha = 100;
            newPoint.creationTime = currentTime;
            trail.push_back(newPoint);
            lastTrailTime = currentTime;
        }

        // Обновление следов
        for (auto it = trail.begin(); it != trail.end(); ) {
            float age = currentTime - it->creationTime;
            float lifeRatio = age / (float)TRAIL_DURATION;
            
            if (lifeRatio > 1.0f) {
                
                it = trail.erase(it);
            } else {
                
                it->radius = 3.0f + lifeRatio * (MAX_RADIUS - 3.0f);
                it->alpha = 100 - static_cast<Uint8>(lifeRatio * 100);
                ++it;
            }
        }

        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        
        
        for (const auto& point : trail) {//следы тусклее точки
            drawCircle(renderer, 
                      static_cast<int>(point.position.getX()), 
                      static_cast<int>(point.position.getY()), 
                      static_cast<int>(point.radius),
                      200, 200, 200, point.alpha);
        }

        
        drawCircle(renderer, 
                  static_cast<int>(position.getX()), 
                  static_cast<int>(position.getY()), 
                  5,
                  255, 255, 255, 255);

        SDL_RenderPresent(renderer);
        
        
        SDL_Delay(10);
    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}