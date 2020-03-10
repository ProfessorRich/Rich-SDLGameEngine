#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SDL_ttf.h>

#include "TextureManager.h"
#include "FontManager.h"
#include "EntityManager.h"

class AssetManager {
private:
	EntityManager* g_entityManager;
	std::map<std::string, SDL_Texture*> m_textures;
	std::map<std::string, TTF_Font*> m_fonts;

public:
	AssetManager(EntityManager* manager);
	~AssetManager();
	void ClearData();

	void AddTexture(std::string textureId, const char* filePath);
	void AddFont(std::string fontId, int fontSize, const char* filePath);

	SDL_Texture* GetTexture(std::string textureId);
	TTF_Font* GetFont(std::string fontId);
};

#endif
