
#include "sprite.h"
#include "SDL2/SDL.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

void Image::load(SDL_Renderer* renderer, const char * filename) {
	FILE* file;
	fopen_s(&file, filename, "rb");

	if (!file) {
		printf("Failed to load file %s\n", filename);
		exit(-1);
	}

	fseek(file, 0L, SEEK_END);
	size_t len = ftell(file);
	rewind(file);

	byte* mem = (byte*)malloc(len);
	
	fread_s((void*)mem, len, len, 1, file);
	fclose(file);

	Header* header = (Header*)mem;
	width = header->width;
	height = header->height;
	has_transparency = header->has_transparency;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

	void* pixels;
	int pitch;

	SDL_LockTexture(texture, 0, &pixels, &pitch);
	memcpy_s(pixels, header->length, mem + sizeof(Header), header->length);
	SDL_UnlockTexture(texture);

	free(mem);

	printf("Loading an image\nFilename: %s\nFilesize: %zu\nHeader Size: %zu\nWidth: %d\nHeight: %d\nTransparency: %s\n", 
		filename, len, sizeof(Header), width, height, has_transparency ? "true" : "false");

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	loaded = true;
}

Image::~Image() {

}
