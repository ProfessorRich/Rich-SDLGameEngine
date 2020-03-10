#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "EntityManager.h"
#include "Map.h"
#include "Game.h"
#include "glm.hpp"
#include <SDL.h>
#include <iostream>

// defined in Game.h - LoadLevel function
extern Map* g_map;												

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
		CheckAndFixBounds();
	}

	void Move(float deltaTime) {
		g_position.x += g_velocity.x * deltaTime;
		g_position.y += g_velocity.y * deltaTime;
	}

	// Clamps entity to boundaries (such as the map...)
	void CheckAndFixBounds() {
		unsigned int xMax = (g_map->GetMapWidth() * g_map->GetTileSize() * g_map->GetScale()) - (g_width * g_scale);
		unsigned int yMax = (g_map->GetMapHeight() * g_map->GetTileSize() * g_map->GetScale()) - (g_height * g_scale);

		if (g_position.x < 0) {
			g_position.x = 0;
			g_velocity.x = 0;
		}

		if (g_position.y < 0) {
			g_position.y = 0;
			g_velocity.y = 0;
		}

		if (g_position.x >= xMax) {
			g_position.x = xMax;
			g_velocity.x = 0;
		}

		if (g_position.y >= yMax) {
			g_position.y = yMax;
			g_velocity.y = 0;
		}
	}

	void Render() {
																						// overridden by SpriteComponent
	}

};

#endif