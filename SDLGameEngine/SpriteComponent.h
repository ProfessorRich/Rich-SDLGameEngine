#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>
#include <string.h>
#include "TextureManager.h"
#include "AssetManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
private:
	TransformComponent* m_transform;
	SDL_Texture* m_texture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

public:
	SDL_RendererFlip g_spriteFlip = SDL_FLIP_NONE;
	
	SpriteComponent(std::string assetTextureId) {
		SetTexture(assetTextureId);
	}

	void SetTexture(std::string assetTextureId) {
		m_texture = Game::g_assetManager->GetTexture(assetTextureId);
	}

	void Initialise() override {
		m_transform = g_owner->GetComponent<TransformComponent>();
		m_sourceRectangle.x = 0;
		m_sourceRectangle.y = 0;
		m_sourceRectangle.w = m_transform->g_width;
		m_sourceRectangle.h = m_transform->g_height;
	}

	void Update(float deltaTime) override {
		m_destinationRectangle.x = (int) m_transform->g_position.x;
		m_destinationRectangle.y = (int) m_transform->g_position.y;
		m_destinationRectangle.w = m_transform->g_width * m_transform->g_scale;
		m_destinationRectangle.h = m_transform->g_height * m_transform->g_scale;
	}

	void Render() override {
		TextureManager::Draw(m_texture, m_sourceRectangle, m_destinationRectangle, g_spriteFlip);
	}

	std::string StringOutputType() {
		return "Component<SpriteComponent>";
	}

};

#endif
