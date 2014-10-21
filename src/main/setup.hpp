// This file is AUTO GENERATED by CMake.
#pragma once

#include "SDL_video.h"

const static char* FILENAME_OVERLAY = "res/overlay/main_normal.png";
const static char* FILENAME_OVERLAY_PRESSED = "res/overlay/main_pressed.png";

#ifdef __ANDROID__

const static char* FILENAME_CONFIG = "/sdcard/cannonball/config.xml";
const static char* FILENAME_SCORES = "/sdcard/cannonball/hiscores";
const static char* FILENAME_TTRIAL = "/sdcard/cannonball/hiscores_timetrial";
const static char* FILENAME_CONT   = "/sdcard/cannonball/hiscores_continuous";
const static int SDL_FLAGS = SDL_SWSURFACE | SDL_DOUBLEBUF;
const static int SDL_BPP = 16;

#else 

const static char* FILENAME_CONFIG = "./config.xml";
const static char* FILENAME_SCORES = "./hiscores";
const static char* FILENAME_TTRIAL = "./hiscores_timetrial";
const static char* FILENAME_CONT   = "./hiscores_continuous";
const static int SDL_FLAGS = SDL_SWSURFACE | SDL_DOUBLEBUF;
const static int SDL_BPP = 32;

#endif
    