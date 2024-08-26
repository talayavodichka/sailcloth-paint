#pragma once
#ifndef SZ
#define SZ

// Safe zone allows drawing
struct SafeZone {
    int x, y, width, height;

    SafeZone(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    void change_safe_zone(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    bool is_safe_zone(int x, int y) {
        return ((x > this->x) && (x < this->width + this->x)) && ((y > this->y) && (y < this->height + this->y));
    }
};

#endif // !SZ