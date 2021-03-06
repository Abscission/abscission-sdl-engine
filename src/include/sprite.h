#pragma once

#include "types.h"
#include <sdl/SDL_render.h>

//Forward declaration of renderer for use with friend
class Renderer;

class Sprite {
private:
	//This is the header used in the Abscission image format
	struct Header {
		unsigned int width;
		unsigned int height;
		unsigned int length;
		unsigned int has_transparency;
	};

	//SDL internal representation of a texture
	SDL_Texture* texture;

	//The width and height of the sprite
	unsigned int width;
	unsigned int height;
	unsigned int has_transparency;

public:
	
	void load(SDL_Renderer* renderer, const char * filename);

	
	~Sprite();

	friend class Renderer;
};