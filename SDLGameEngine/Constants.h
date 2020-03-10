#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int G_WINDOW_WIDTH = 1600;
const unsigned int G_WINDOW_HEIGHT = 900;

const unsigned int G_TARGET_FPS = 120;
const unsigned int G_TARGET_DELTA_MS = 1000 / G_TARGET_FPS;

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

//const float G_GRAVITY = 980.0f;
//const float G_DRAG = 10.0f;
//const float G_FRICTION = 10.0f;
//const float G_RESTITUTION = 0.8; // The coefficient of restitution = percentage of velocity maintained in a bounce

#endif
