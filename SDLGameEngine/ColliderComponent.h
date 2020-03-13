#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SDL.h>
#include <string>

#include "Game.h"
#include "EntityManager.h"
#include "TransformComponent.h"

class ColliderComponent : public Component {
public:
	std::string g_colliderTag;
	SDL_Rect g_hitBox;
	TransformComponent* g_transform;

	ColliderComponent(std::string colliderTag) {
		g_colliderTag = colliderTag;
		g_hitBox = { 0, 0, 0, 0 };  // I wonder if this will cause problems...
	}

	ColliderComponent(std::string colliderTag, int positionX, int positionY, int width, int height) {
		g_colliderTag = colliderTag;
		g_hitBox = { positionX, positionY, width, height };
	}

	void Initialise() override {
		if (g_owner->HasComponent<TransformComponent>()) {
			g_transform = g_owner->GetComponent<TransformComponent>();
		}
	}

	void Update(float deltaTime) override {
		g_hitBox.x = static_cast<int>(g_transform->g_position.x);
		g_hitBox.y = static_cast<int>(g_transform->g_position.y);
		g_hitBox.w = g_transform->g_width * g_transform->g_scale;
		g_hitBox.h = g_transform->g_height * g_transform->g_scale;
	}

	void Render() override {

		//if G_DEBUG then render the hit box.
		if (G_DEBUG) {
			SDL_Rect renderHitBox = g_hitBox;

			renderHitBox.x -= Game::g_camera.x;
			renderHitBox.y -= Game::g_camera.y;

			SDL_SetRenderDrawColor(Game::g_renderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(Game::g_renderer, &renderHitBox);	
		}
	}

};

#endif