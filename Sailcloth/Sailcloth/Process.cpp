#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Process.h"

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
bool isDrawing = false;
short startX = 0, startY = 0, endX = 0, endY = 0;

void process_control::init(unsigned short WIDTH, unsigned short HEIGHT) {
    if (!al_init()) {
        return;
    }

    al_install_mouse();
    al_install_keyboard();

    display = al_create_display(WIDTH, HEIGHT);
    if (!display) {
        return;
    }

    al_set_window_title(display, "SailCloth");
    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_init_primitives_addon();

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_flip_display();
}

void process_control::run(unsigned short WIDTH, unsigned short HEIGHT) {
    process_control::init(WIDTH, HEIGHT);
    
    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            startX = event.mouse.x;
            startY = event.mouse.y;

            if (event.mouse.button == 2) {
                al_clear_to_color(al_map_rgb(255, 255, 255));
            }
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            endX = event.mouse.x;
            endY = event.mouse.y;
            al_draw_line(startX, startY, endX, endY, al_map_rgb(0, 0, 0), 10);
        }

        al_flip_display();
    }

    process_control::destroy();
}

void process_control::destroy() {
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}