#ifndef CONSTANTS_H
#define CONSTANTS_H

// set true to enable debug features
const bool G_DEBUG = true;						

const unsigned int G_WINDOW_WIDTH = 1600;
const unsigned int G_WINDOW_HEIGHT = 900;

const unsigned int G_FPS_COUNTER_WIDTH = 100;
const unsigned int G_FPS_COUNTER_HEIGHT = 21;

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

#endif
