#pragma once
#ifndef P
#define P

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

namespace process_control {
    void init(unsigned short WIDTH, unsigned short HEIGHT);
	void run(unsigned short WIDTH, unsigned short HEIGHT);
	void destroy();
}

#endif // !P