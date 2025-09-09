// TrailPoint.h
#pragma once
#include "Vector2D.h"
#include <SDL2/SDL.h>

class TrailPoint {
private:
    Vector2D position;
    float radius;
    Uint8 alpha;
    Uint32 creationTime;

public:
    TrailPoint();
    TrailPoint(const Vector2D& pos, float rad, Uint8 a, Uint32 time);
    
    const Vector2D& getPosition() const;
    float getRadius() const;
    Uint8 getAlpha() const;
    Uint32 getCreationTime() const;
    
    void setPosition(const Vector2D& pos);
    void setRadius(float rad);
    void setAlpha(Uint8 a);
    void setCreationTime(Uint32 time);
    
    void update(float lifeRatio, float maxRadius);
};