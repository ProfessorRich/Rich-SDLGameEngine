#include "Animation.h"

Animation::Animation() {

}

Animation::Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed) {
	g_index = index;
	g_numFrames = numFrames;
	g_animationSpeed = animationSpeed;
}