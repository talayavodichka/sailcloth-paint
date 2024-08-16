#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#pragma once
#ifndef B
#define B

struct Button {
    int x, y, width, height;
    ALLEGRO_COLOR color;

    Button(int x, int y, int width, int height, ALLEGRO_COLOR color)
        : x(x), y(y), width(width), height(height), color(color) {}

    void draw_button() {
        al_draw_filled_rectangle(this->x, this->y, this->x + this->width, this->y + this->height, this->color);
    }

    void draw_button(ALLEGRO_BITMAP* bitmap, int flags) {
        al_draw_bitmap(bitmap, this->x, this->y, flags);
    }
};

#endif // !B