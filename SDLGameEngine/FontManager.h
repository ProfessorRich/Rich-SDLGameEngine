#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "Game.h"

class FontManager {
public:
	static TTF_Font* LoadFont(const char* filePath, int fontSize);
	static void Draw(SDL_Texture* texture, SDL_Rect destinationRectangle);
	
};

#endif 

