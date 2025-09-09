// Vector2D.h
#pragma once

class Vector2D {
private:
    float x;
    float y;

public:
    Vector2D(float x = 0.0f, float y = 0.0f);
    
    float getX() const;
    float getY() const;
    
    void setX(float newX, float minX, float maxX);
    void setY(float newY, float minY, float maxY);
    void setPosition(float newX, float newY, float minX, float maxX, float minY, float maxY);

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(float scalar) const;

    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
    Vector2D& operator*=(float scalar);
    Vector2D& operator/=(float scalar);
    
    bool isZero() const;
};