#!/bin/bash

SOURCES="src/player.cpp src/audio.cpp src/card.cpp src/config.cpp src/console.cpp src/con_vars.cpp src/database.cpp src/events.cpp src/game_state.cpp src/gs_cardgame.cpp src/gs_menu.cpp src/input.cpp src/main.cpp src/renderer.cpp src/sprite.cpp 
src/windowing.cpp src/gs_battle.cpp"

CFLAGS="-D_REENTRANT -I/usr/include/SDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2"
echo $SOURCES
echo $CFLAGS

g++ $SOURCES $CFLAGS -Isrc/include --std=gnu++14 -o game 
