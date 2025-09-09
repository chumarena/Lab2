// Vector2D.cpp
#include "Vector2D.h"
#include <algorithm>

Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

float Vector2D::getX() const { return x; }
float Vector2D::getY() const { return y; }

void Vector2D::setX(float newX, float minX, float maxX) {
    x = std::max(minX, std::min(maxX, newX));
}

void Vector2D::setY(float newY, float minY, float maxY) {
    y = std::max(minY, std::min(maxY, newY));
}

void Vector2D::setPosition(float newX, float newY, float minX, float maxX, float minY, float maxY) {
    setX(newX, minX, maxX);
    setY(newY, minY, maxY);
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(float scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(float scalar) const {
    return Vector2D(x / scalar, y / scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2D& Vector2D::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2D& Vector2D::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

bool Vector2D::isZero() const {
    return (x == 0.0f && y == 0.0f);
}