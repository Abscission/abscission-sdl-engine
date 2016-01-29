#pragma once

#include "SDL2\SDL_mixer.h"

class SoundManager {
public:
	void init();
	void play_file(char* file);
	void play_file_loop(char* file);

};

extern SoundManager g_sound_manager;