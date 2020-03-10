#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>
#include <string.h>
#include "TextureManager.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "Animation.h"

class SpriteComponent : public Component {
private:
	TransformComponent* m_transform;
	SDL_Texture* m_texture;
	SDL_Rect m_sourceRectangle;						// the rectangle in the m_texture which contains the current sprite to be drawn
	SDL_Rect m_destinationRectangle;				// the rectangle where the current sprite will be drawn on the screen
	bool m_isAnimated;
	int m_numFrames;
	int m_animationSpeed;							// m_animationSpeed should be set between 1 and 10 
	bool m_isFixed;
	std::map<std::string, Animation> m_animations;
	std::string m_currentAnimationName;
	unsigned int m_animationIndex = 0;				// what 'row' of animations are used - in order to allow multi-direction animations etc.

public:
	SDL_RendererFlip g_spriteFlip = SDL_FLIP_NONE;
	
	SpriteComponent(std::string assetTextureId) {
		m_isAnimated = false;
		m_isFixed = false;
		SetTexture(assetTextureId);
	}

	SpriteComponent(std::string assetTextureId, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
		m_isAnimated = true;
		SetTexture(assetTextureId);
		m_numFrames = numFrames;
		m_animationSpeed = animationSpeed;
		m_isFixed = isFixed;

		if (hasDirections) {
			Animation downAnimation = Animation(0, m_numFrames, m_animationSpeed);
			Animation rightAnimation = Animation(1, m_numFrames, m_animationSpeed);
			Animation leftAnimation = Animation(2, m_numFrames, m_animationSpeed);
			Animation upAnimation = Animation(3, m_numFrames, m_animationSpeed);
			m_animations.emplace("Down", downAnimation);
			m_animations.emplace("Right", rightAnimation);
			m_animations.emplace("Left", leftAnimation);
			m_animations.emplace("Up", upAnimation);

			m_animationIndex = 0;
			m_currentAnimationName = "Down";
		}
		else {
			Animation singleDirectionAnimation = Animation(0, m_numFrames, m_animationSpeed);
			m_animations.emplace("SingleAnimation", singleDirectionAnimation);
			m_animationIndex = 0;
			m_currentAnimationName = "SingleAnimation";
		}

		Play(m_currentAnimationName);

		SetTexture(assetTextureId);
	}

	void Play(std::string animationName) {
		m_numFrames = m_animations[animationName].g_numFrames;
		m_animationIndex = m_animations[animationName].g_index;
		m_animationSpeed = m_animations[animationName].g_animationSpeed;

		m_currentAnimationName = animationName;
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
		if (m_isAnimated) {
			m_sourceRectangle.x = (m_sourceRectangle.w * (static_cast<int>(SDL_GetTicks() / (1000 - ((1000 - 50) / 9) * (m_animationSpeed - 1))) % m_numFrames)); // Superl33t formula to ensure m_animationSpeed 1 - 10 provides number from 1000 to 50 which translates to speed which m_numFrames cycles. All my own work.
		}
		m_sourceRectangle.y = m_animationIndex * m_transform->g_height;

		// If m_isFixed (GUI elements etc) then don't adjust for camera.
		if (m_isFixed) {
			m_destinationRectangle.x = static_cast<int>(m_transform->g_position.x);
			m_destinationRectangle.y = static_cast<int>(m_transform->g_position.y);
		}
		else {
			m_destinationRectangle.x = static_cast<int>(m_transform->g_position.x) - Game::g_camera.x;
			m_destinationRectangle.y = static_cast<int>(m_transform->g_position.y) - Game::g_camera.y;
		}

		m_destinationRectangle.w = m_transform->g_width * m_transform->g_scale;
		m_destinationRectangle.h = m_transform->g_height * m_transform->g_scale;
	}

	void Render() override {
		TextureManager::Draw(m_texture, m_sourceRectangle, m_destinationRectangle, g_spriteFlip);
	}

	/*std::string StringOutputType() {
		return "Component<SpriteComponent>";
	}*/

};

#endif
