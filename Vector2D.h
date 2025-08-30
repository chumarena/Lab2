#pragma once
#include <iostream>

class Vector2D {
private:

    float x, y;

public:
    

    // Конструкторы
    Vector2D(float x = 0, float y = 0) : x(x), y(y) {}

    float getX() const { return x;};
    float getY() const { return y;};
    
    // Методы установки значений с проверкой границ
    void setX(float newX, float minX, float maxX);
    
    
    void setY(float newY, float minY, float maxY);
    
    
    void setPosition(float newX, float newY, float minX, float maxX, float minY, float maxY);

    // Операторы
    Vector2D operator+(const Vector2D& other) const;


    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;

    Vector2D operator/(float scalar) const;

    Vector2D& operator+=(const Vector2D& other);

    Vector2D& operator-=(const Vector2D& other);

    Vector2D& operator*=(float scalar);

    Vector2D& operator/=(float scalar);
    
    // Проверка на нулевой вектор
    bool isZero() const;
    
};