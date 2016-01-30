#pragma once

#include <string>
#include "renderer.h"


class Console {
private:
	bool textbox_active = false;

	bool open = false;
	int console_width = 780;
	int console_height = 580;
	int console_x = 10;
	int console_y = 10;

	bool dragging = false;
	int drag_x = 0;
	int drag_y = 0;

	bool resizing_x = false;
	bool resizing_y = false;

	std::string console_backlog = "";
public:
	void draw();
	std::string run_command(std::string command);
};

extern Console console;