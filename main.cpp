#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// Класс геометрический вектор
class Vector2D {
private:

    float x, y;

public:
    

    // Конструкторы
    Vector2D(float x = 0, float y = 0) : x(x), y(y) {}

    // Операторы
    Vector2D operator+(const Vector2D& other) const {//зачем const у функции
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D operator/(float scalar) const {
        return Vector2D(x / scalar, y / scalar);
    }

    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2D& operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2D& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2D& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    
    // Проверка на нулевой вектор
    bool isZero() const {
        return x == 0 && y == 0;
    }
};

// Быстрая функция для рисования круга
void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    
    // Используем алгоритм Брезенхэма для рисования круга
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);


        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
    
    // Заливаем круг горизонтальными линиями
    for (int dy = -radius; dy <= radius; dy++) {
        int dx = static_cast<int>(std::sqrt(radius * radius - dy * dy));
        SDL_RenderDrawLine(renderer, centerX - dx, centerY + dy, centerX + dx, centerY + dy);
    }
}

// Структура для хранения информации о следе
struct TrailPoint {
    Vector2D position;
    float radius;
    Uint8 alpha;// unsigned int 8 - количество нужных битов
    Uint32 creationTime;
};

int main(int argc, char* argv[]) {
    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Ошибка инициализации SDL: %s", SDL_GetError());
        return 1;
    }

    // Создание окна и рендерера
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

    // Параметры точки
    Vector2D position(WIDTH / 2, HEIGHT / 2);
    Vector2D velocity(0, 0);
    const float SPEED = 2.0f;

    // Параметры следа
    std::vector<TrailPoint> trail;
    const Uint32 TRAIL_DELAY = 100;
    Uint32 lastTrailTime = 0;
    const float MAX_RADIUS = 20.0f;
    const int TRAIL_DURATION = 1500;
    
    // Переменная для отслеживания движения
    bool isMoving = false;

    // Основной цикл
    bool running = true;
    SDL_Event event;
    //Uint32 lastTime = SDL_GetTicks();
    
    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        //float deltaTime = (currentTime - lastTime) / 1000.0f;
        //lastTime = currentTime;

        // Обработка событий
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        velocity.y = -SPEED;// все ошибки можно исправить через getter и setter
                        break;
                    case SDLK_DOWN:
                        velocity.y = SPEED;
                        break;
                    case SDLK_LEFT:
                        velocity.x = -SPEED;
                        break;
                    case SDLK_RIGHT:
                        velocity.x = SPEED;
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_DOWN:
                        velocity.y = 0;
                        break;
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        velocity.x = 0;
                        break;
                }
            }
        }

        // Обновление позиции точки
        position += velocity;
        
        // Ограничение движения в пределах окна
        position.x = std::max(5.0f, std::min((float)WIDTH - 5, position.x));//getter setter надо юзать, напрямую нельзя изменять
        position.y = std::max(5.0f, std::min((float)HEIGHT - 5, position.y));

        // Проверка, движется ли точка
        isMoving = !velocity.isZero();
        
        // Добавление нового следа только если точка движется
        if (isMoving && currentTime - lastTrailTime > TRAIL_DELAY) {
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
                // Удаление старых следов
                it = trail.erase(it);
            } else {
                // Обновление радиуса и прозрачности
                it->radius = 3.0f + lifeRatio * (MAX_RADIUS - 3.0f);
                it->alpha = 100 - static_cast<Uint8>(lifeRatio * 100);
                ++it;
            }
        }

        // Отрисовка
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Отрисовка следов (тусклые)
        for (const auto& point : trail) {
            drawCircle(renderer, 
                      static_cast<int>(point.position.x), 
                      static_cast<int>(point.position.y), 
                      static_cast<int>(point.radius),
                      200, 200, 200, point.alpha);
        }

        // Отрисовка текущей точки (яркая)
        drawCircle(renderer, 
                  static_cast<int>(position.x), 
                  static_cast<int>(position.y), 
                  5,
                  255, 255, 255, 255);

        SDL_RenderPresent(renderer);
        
        // Небольшая задержка для контроля FPS
        SDL_Delay(10);
    }

    // Очистка ресурсов
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}