// TrailPoint.cpp
#include "TrailPoint.h"

TrailPoint::TrailPoint() : radius(0.0f), alpha(0), creationTime(0) {}

TrailPoint::TrailPoint(const Vector2D& pos, float rad, Uint8 a, Uint32 time) 
    : position(pos), radius(rad), alpha(a), creationTime(time) {}

const Vector2D& TrailPoint::getPosition() const { return position; }
float TrailPoint::getRadius() const { return radius; }
Uint8 TrailPoint::getAlpha() const { return alpha; }
Uint32 TrailPoint::getCreationTime() const { return creationTime; }

void TrailPoint::setPosition(const Vector2D& pos) { position = pos; }
void TrailPoint::setRadius(float rad) { radius = rad; }
void TrailPoint::setAlpha(Uint8 a) { alpha = a; }
void TrailPoint::setCreationTime(Uint32 time) { creationTime = time; }

void TrailPoint::update(float lifeRatio, float maxRadius) {
    radius = 3.0f + lifeRatio * (maxRadius - 3.0f);
    alpha = 100 - static_cast<Uint8>(lifeRatio * 100);
}