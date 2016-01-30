#include "audio.h"
#include <cstdio>

void SoundManager::init() {
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

void SoundManager::play_file(char * file) {
	Mix_Music* music = Mix_LoadMUS(file);
	Mix_PlayMusic(music, 1);
}

void SoundManager::play_file_loop(char * file) {
	Mix_Music* music = Mix_LoadMUS(file);
	Mix_PlayMusic(music, -1); 
}


SoundManager g_sound_manager;