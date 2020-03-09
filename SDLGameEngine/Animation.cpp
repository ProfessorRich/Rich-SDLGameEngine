#include "Animation.h"

Animation::Animation() {
	g_index = 0;
	g_numFrames = 1;
	g_animationSpeed = 1;
}

Animation::Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed) {
	g_index = index;
	g_numFrames = numFrames;
	g_animationSpeed = animationSpeed;
}