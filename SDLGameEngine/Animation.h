#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
	unsigned int g_index;
	unsigned int g_numFrames;
	unsigned int g_animationSpeed;

	Animation();
	Animation(unsigned int, unsigned int, unsigned int);
};

#endif
