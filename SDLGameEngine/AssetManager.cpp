#include "AssetManager.h"

AssetManager::AssetManager(EntityManager* manager) : g_entityManager(manager) {

}

void AssetManager::ClearData() {
	m_textures.clear();
	m_fonts.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {
	m_textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

void AssetManager::AddFont(std::string fontId, int fontSize, const char* filePath) {
	m_fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
	return m_textures.at(textureId);
}

TTF_Font* AssetManager::GetFont(std::string fontId) {
	return m_fonts.at(fontId);
}
