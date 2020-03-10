#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "EntityManager.h"
#include "Game.h"
#include "glm.hpp"
#include <SDL.h>
#include <iostream>

class KeyboardInputComponent; 

class TransformComponent : public Component {
public:
	glm::vec2 g_position;
	glm::vec2 g_velocity;
	int g_width;
	int g_height;
	int g_scale;

	TransformComponent(int posX, int posY, int velX, int velY, int width, int height, int scale) {
		g_position = glm::vec2(posX, posY);
		g_velocity = glm::vec2(velX, velY);
		g_width = width;
		g_height = height;
		g_scale = scale;
	}

	void Initialise() {
	}

	void Update(float deltaTime) {
		Move(deltaTime);
		if (g_owner->HasComponent<KeyboardInputComponent>()) {		// if it's a controllable entity, keep it in certain boundaries
			FixBounds();
		}
	}

	void Move(float deltaTime) {
		g_position.x += g_velocity.x * deltaTime;
		g_position.y += g_velocity.y * deltaTime;
	}

	// Clamps entity to boundaries (such as the map...)
	void FixBounds() {

		/*
		float xLimit = static_cast<float>((G_WINDOW_WIDTH) - (g_width * g_scale));			// TODO: Fix this bs
		float yLimit = static_cast<float>((G_WINDOW_HEIGHT) - (g_height * g_scale));

		
		if (g_position.x < 0) {
			g_position.x = 0;
			g_velocity.x = 0;
		}
		if (g_position.x > xLimit) {
			g_position.x = xLimit;
			g_velocity.x = 0;
		}

		if (g_position.y < 0) {
			g_position.y = 0;
			g_velocity.y = 0;
		}

		if (g_position.y > yLimit) {
			g_position.y = yLimit;
			g_velocity.y = 0;
		}*/
	}

	void Render() {

	}

	/*std::string StringOutputType() {
		return "Component<TransformComponent>";
	}*/
};

#endif