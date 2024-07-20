#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Process.h"
#include "Button.h"
#include "Color.h"
#include "SafeZone.h"

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;

ALLEGRO_BITMAP* icon = NULL;
ALLEGRO_SAMPLE* clear_snd = NULL;

ALLEGRO_COLOR curr_color;
std::vector<Button> buttons = {
    { 5, 5, 20, 20, RED },
    { 30, 5, 20, 20, GREEN },
    { 55, 5, 20, 20, BLUE },
    { 80, 5, 20, 20, YELLOW },
    { 105, 5, 20, 20, PINK },
    { 130, 5, 20, 20, CYAN },
};
SafeZone sz(0, 40, 640, 440);
bool isDrawing = false;

void process_control::init(unsigned short WIDTH, unsigned short HEIGHT) {
    curr_color = al_map_rgb(0, 0, 0);

    if (!al_init()) return;

    al_install_mouse();
    al_install_keyboard();
    al_install_audio();

    display = al_create_display(WIDTH, HEIGHT);
    if (!display) return;

    al_set_window_title(display, "SailCloth");
    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_init_primitives_addon();
    al_init_image_addon();
    al_init_acodec_addon();

    for (int i = 0; i < buttons.size(); ++i) buttons[i].draw_button();

    event_queue = al_create_event_queue();
    if (!event_queue) return;

    al_reserve_samples(1);

    icon = al_load_bitmap("img/icon.png");
    clear_snd = al_load_sample("snd/clear_snd.wav");
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
    al_set_display_icon(display, icon);
    al_flip_display();
}

void process_control::run(unsigned short WIDTH, unsigned short HEIGHT) {
    process_control::init(WIDTH, HEIGHT);
    
    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (sz.is_safe_zone(event.mouse.x, event.mouse.y)) isDrawing = true;

            for (auto& button : buttons) {
                if (event.mouse.x >= button.x && event.mouse.x <= button.x + button.width &&
                    event.mouse.y >= button.y && event.mouse.y <= button.y + button.height) {
                    curr_color = button.color;
                }
            }

            if (event.mouse.button == 2) {
                isDrawing = false;
                al_play_sample(clear_snd, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                al_clear_to_color(al_map_rgb(255, 255, 255));
                for (int i = 0; i < buttons.size(); ++i) {
                    buttons[i].draw_button();
                }
            }
        }
        else if ((event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) || (!sz.is_safe_zone(event.mouse.x, event.mouse.y))) {
            isDrawing = false;
            al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
        }

        if (isDrawing) {
            al_draw_filled_circle(event.mouse.x, event.mouse.y, 10, curr_color);
            al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_PRECISION);
        }

        al_flip_display();
    }

    process_control::destroy();
}

void process_control::destroy() {
    al_destroy_bitmap(icon);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}