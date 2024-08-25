#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#pragma once
#ifndef P
#define P

namespace process_control {
    void init(unsigned short WIDTH, unsigned short HEIGHT);
	void run(unsigned short WIDTH, unsigned short HEIGHT);
	void destroy();
}

#endif // !P