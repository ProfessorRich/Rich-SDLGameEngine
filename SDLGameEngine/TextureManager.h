#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect m_destinationRectangle, SDL_RendererFlip flip);
};

#endif