class Vector2D {
private:

    float x, y;

public:
    

    // Конструкторы
    Vector2D(float x = 0, float y = 0) : x(x), y(y) {}

    float getX() const { return x; }
    float getY() const { return y; }
    
    // Методы установки значений с проверкой границ
    void setX(float newX, float minX, float maxX) {
        x = std::max(minX, std::min(maxX, newX));
    }
    
    void setY(float newY, float minY, float maxY) {
        y = std::max(minY, std::min(maxY, newY));
    }
    
    void setPosition(float newX, float newY, float minX, float maxX, float minY, float maxY) {
        setX(newX, minX, maxX);
        setY(newY, minY, maxY);
    }

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