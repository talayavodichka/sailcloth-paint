#pragma once
#ifndef T
#define T

#define COLOR_BUTTON 0
#define SAVE_BUTTON 1
#define CLEAR_BUTTON 2
#define ERASER_BUTTON 3

const char* get_tip(int flag) {
	switch (flag) {
	case COLOR_BUTTON:
		return "Pick color.";
	case SAVE_BUTTON:
		return "Save picture.";
	case CLEAR_BUTTON:
		return "Clear all.";
	case ERASER_BUTTON:
		return "Pick an eraser.";
	default:
		return "NULL";
	}
}

#endif // !T