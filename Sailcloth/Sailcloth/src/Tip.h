#pragma once
#ifndef T
#define T

const char* get_tip(int flag) {
	switch (flag) {
	case 0:
		return "Color button.";
	case 1:
		return "Save picture.";
	default:
		return "NULL";
	}
}

#endif // !T