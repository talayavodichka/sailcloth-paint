#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#pragma once
#ifndef SZ
#define SZ

struct SafeZone {
    int x, y, width, height;
    SafeZone(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}
    bool Check(int x, int y) {
        return ((x > this->x) && (x < this->width + this->x)) && ((y > this->y) && (y < this->height + this->y));
    }
};

#endif // !SZ