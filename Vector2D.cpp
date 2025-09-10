#include "Vector2D.h"



    

    // Конструкторы
    
    
    // Методы установки значений с проверкой границ
    void Vector2D::setX(float newX, float minX, float maxX) {
        x = std::max(minX, std::min(maxX, newX));
    }
    
    void Vector2D::setY(float newY, float minY, float maxY) {
        y = std::max(minY, std::min(maxY, newY));
    }
    
    void  Vector2D::setPosition(float newX, float newY, float minX, float maxX, float minY, float maxY) {
        setX(newX, minX, maxX);
        setY(newY, minY, maxY);
    }

    // Операторы
    Vector2D  Vector2D::operator+(const Vector2D& other) const {//зачем const у функции
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D  Vector2D::operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D  Vector2D::operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D  Vector2D::operator/(float scalar) const {
        return Vector2D(x / scalar, y / scalar);
    }

    Vector2D&  Vector2D::operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2D&  Vector2D::operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2D&  Vector2D::operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2D&  Vector2D::operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    
    // Проверка на нулевой вектор
    bool  Vector2D::isZero() const {
        return x == 0 && y == 0;
    }

    
