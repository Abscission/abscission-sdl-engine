#pragma once

#include "sdl\SDL_mixer.h"

class SoundManager {
public:
	void init();
	void play_file(char* file);
};

extern SoundManager g_sound_manager;