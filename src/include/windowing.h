#pragma once

class Window {
private:
	bool _open = false;
	int width = 780;
	int height = 580;
	int x = 10;
	int y = 10;

	bool dragging = false;
	int drag_x = 0;
	int drag_y = 0;

	bool resizing_x = false;
	bool resizing_y = false;

public:
	void open();
	void close();
	void toggle_open();

	void update_and_draw();
};