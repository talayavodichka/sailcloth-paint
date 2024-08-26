#include <vector>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "Process.h"
#include "Button.h"
#include "Color.h"
#include "SafeZone.h"
#include "SavePicture.h"
#include "Tip.h"

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;

ALLEGRO_FONT* tips_fnt = NULL;

ALLEGRO_BITMAP* program_img = NULL;
ALLEGRO_BITMAP* clear_img = NULL;
ALLEGRO_BITMAP* save_img = NULL;

ALLEGRO_SAMPLE* clear_snd = NULL;

ALLEGRO_COLOR curr_color;
std::vector<Button> buttons = {
    { 5, 5, 20, 20, RED },
    { 30, 5, 20, 20, GREEN },
    { 55, 5, 20, 20, BLUE },
    { 80, 5, 20, 20, YELLOW },
    { 105, 5, 20, 20, PINK },
    { 130, 5, 20, 20, CYAN },
    { 155, 5, 20, 20, BLACK },
};
SafeZone sz(0, 40, SCREEN_WIDTH - 60, SCREEN_HEIGHT - 40);
bool isDrawing = false;
bool isTip = false;

const char* tipText = "NULL";

void process_control::init(unsigned short WIDTH, unsigned short HEIGHT) {
    curr_color = BLACK;

    // ALLEGRO INITS
    if (!al_init()) return;

    al_install_mouse();
    al_install_keyboard();
    al_install_audio();

    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    al_set_new_display_flags(ALLEGRO_NOFRAME);
    display = al_create_display(WIDTH, HEIGHT);
    if (!display) return;

    al_set_window_title(display, "SailCloth");
    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_init_primitives_addon();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // UI DRAW
    for (int i = 0; i < buttons.size(); ++i) buttons[i].draw_button();
    al_draw_line(0, 28, 1920, 28, BLACK, 2);

    event_queue = al_create_event_queue();
    if (!event_queue) return;

    al_reserve_samples(1);

    // RESOURCES
    tips_fnt = al_load_ttf_font("fnt/tips.ttf", 22, NULL);

    program_img = al_load_bitmap("img/program_icon.png");
    // clear_img = al_load_bitmap("img/clear_icon.png");
    save_img = al_load_bitmap("img/save_icon.png");

    clear_snd = al_load_sample("snd/clear_snd.wav");
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
    al_set_display_icon(display, program_img);
    al_draw_bitmap(save_img, 1880, 5, 0);
    al_flip_display();
}

void process_control::run(unsigned short WIDTH, unsigned short HEIGHT) {
    process_control::init(WIDTH, HEIGHT);
    
    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (sz.is_safe_zone(event.mouse.x, event.mouse.y)) isDrawing = true;

            for (auto& button : buttons) {
                if (event.mouse.x >= button.x && event.mouse.x <= button.x + button.width &&
                    event.mouse.y >= button.y && event.mouse.y <= button.y + button.height) {
                    curr_color = button.color;
                }
            }

            if (event.mouse.x >= 1880 && event.mouse.x <= 1900 &&
                event.mouse.y >= 5 && event.mouse.y <= 25) {
                take_screenshot("sailcloth.png");
            }

            if (event.mouse.button == 2) {
                isDrawing = false;
                al_play_sample(clear_snd, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                al_clear_to_color(al_map_rgb(255, 255, 255));
                // UI REDRAW
                for (int i = 0; i < buttons.size(); ++i) buttons[i].draw_button();
                al_draw_line(0, 28, 1920, 28, BLACK, 2);
                al_draw_bitmap(save_img, 175, 5, 0);
            }
        }
        else if ((event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) || (!sz.is_safe_zone(event.mouse.x, event.mouse.y))) {
            isDrawing = false;
            al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
        }

        // TIPS
        for (auto& button : buttons) {
            if (event.mouse.x >= button.x && event.mouse.x <= button.x + button.width &&
                event.mouse.y >= button.y && event.mouse.y <= button.y + button.height) {
                isTip = true;
                tipText = get_tip(0);
            }
        }

        if (event.mouse.x >= 1880 && event.mouse.x <= 1900 &&
            event.mouse.y >= 5 && event.mouse.y <= 25) {
            isTip = true;
            tipText = get_tip(1);
        }

        if (isDrawing) {
            al_draw_filled_circle(event.mouse.x, event.mouse.y, 10, curr_color);
            al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_PRECISION);
        }

        if (isTip) {
            al_draw_text(tips_fnt, BLACK, 20, 1040, 0, tipText);
        }
        else {
            al_draw_filled_rectangle(0, 1025, 1920, 1080, WHITE);
        }
        isTip = false;

        al_flip_display();
    }

    process_control::destroy();
}

void process_control::destroy() {
    al_destroy_font(tips_fnt);

    al_destroy_bitmap(program_img);
    al_destroy_bitmap(clear_img);
    al_destroy_bitmap(save_img);

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}