#pragma once

#include "SDL2/SDL_mixer.h"

class SoundManager {
public:
	void init();
	void play_file(const char* file);
	void play_file_loop(const char* file);

};

extern SoundManager g_sound_manager;