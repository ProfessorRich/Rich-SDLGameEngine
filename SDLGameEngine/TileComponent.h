#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include <SDL.h>
#include <glm.hpp>
#include "AssetManager.h"
#include "EntityManager.h"


class TileComponent : public Component {
public:
	SDL_Texture* m_texture;
	SDL_Rect m_sourceRect;
	SDL_Rect m_destRect;
	glm::vec2 m_position;

	TileComponent(int sourceRectX, int sourceRectY, int destX, int destY, int tileSize, int tileScale, std::string assetTextureId) {
		m_texture = Game::g_assetManager->GetTexture(assetTextureId);

		m_sourceRect.x = sourceRectX;
		m_sourceRect.y = sourceRectY;
		m_sourceRect.w = tileSize;
		m_sourceRect.h = tileSize;			// Assumes squares... a good assumption.

		m_destRect.x = destX;
		m_destRect.y = destY;
		m_destRect.w = tileSize * tileScale;
		m_destRect.h = tileSize * tileScale;

		m_position.x = destX;
		m_position.y = destY;
	}

	~TileComponent() {

	}

	void Update(float deltaTime) override {
		// TODO: Needed when camera controls come up. Tiles need to move as 'camera' moves.
	}

	void Render() override {
		TextureManager::Draw(m_texture, m_sourceRect, m_destRect, SDL_FLIP_NONE);
	}
};

#endif
