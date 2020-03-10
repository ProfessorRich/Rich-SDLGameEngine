#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "Game.h"
#include <SDL.h>
#include <SDL_ttf.h>

class FontManager {
public:
	static TTF_Font* LoadFont(const char* filePath, int fontSize);
	static void Draw(SDL_Texture* texture, SDL_Rect destinationRectangle);
	
};

#endif 

