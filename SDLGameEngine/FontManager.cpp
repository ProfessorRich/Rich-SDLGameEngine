#include "FontManager.h"

TTF_Font* FontManager::LoadFont(const char* filePath, int fontSize) {
	return TTF_OpenFont(filePath, fontSize);
}

void FontManager::Draw(SDL_Texture* texture, SDL_Rect destinationRectangle) {
	SDL_RenderCopy(Game::g_renderer, texture, NULL, &destinationRectangle);
}