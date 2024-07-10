#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#pragma once
#ifndef Process
#define Process

namespace process_control {
    void init(unsigned short WIDTH, unsigned short HEIGHT);
	void run(unsigned short WIDTH, unsigned short HEIGHT);
	void destroy();
}

#endif // !Process