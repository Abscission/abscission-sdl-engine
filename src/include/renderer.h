#pragma once

#include "SDL/SDL_render.h"

#include "sprite.h"

//This class handles rendering
class Renderer {
public:
	//These are the SDL internal representaions of windows and renderers
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	
	Renderer(int width = 800, int height = 600, const char * title = "Abscission SDL Engine 1.0.0");

	void init(int width = 800, int height = 600, const char * title = "Abscission SDL Engine 1.0.0");

	~Renderer();
	
	//draw the sprite spr at location {x, y} with a scale factor of scale
	void draw_sprite(Sprite& spr, int x = 0, int y = 0, float scale = 1.0f);

	SDL_Rect draw_text(const char * text, int x, int y, int font_size, SDL_Color c = SDL_Color{ 255, 255,255,255 });

	//Call this after all drawing is finished each frame
	void refresh();
};

extern Renderer* g_renderer;