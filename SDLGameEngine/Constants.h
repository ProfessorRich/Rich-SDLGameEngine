#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL.h>

// set true to enable debug features
const bool G_DEBUG = true;						

const unsigned int G_WINDOW_WIDTH = 1600;
const unsigned int G_WINDOW_HEIGHT = 900;

const unsigned int G_FPS_COUNTER_POSX = 10;
const unsigned int G_FPS_COUNTER_POSY = 10;

const unsigned int G_TARGET_FPS = 120;
const float G_TARGET_DELTA_MS = 1000.0f / G_TARGET_FPS;

enum RenderLayer {
	G_TILEMAP_LAYER = 0,
	G_DECOR_LAYER = 1,
	G_WILDLIFE_LAYER = 2,
	G_COLLECTABLE_LAYER = 3,
	G_NPC_LAYER = 4,
	G_PLAYER_LAYER = 5,
	G_PROJECTILE_LAYER = 6,
	G_SKY_LAYER = 7, 
	G_GUI_LAYER = 8
};

const unsigned int G_NUM_RENDER_LAYERS = 9;

const SDL_Colour G_WHITE_COLOUR = { 255,255,255,255 };
const SDL_Colour G_RED_COLOUR = { 255,0,0,255 };

#endif
