#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "EntityManager.h"
#include "Game.h"
#include "glm.hpp"
#include <SDL.h>
#include <iostream>

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
		g_position.x += g_velocity.x*deltaTime;
		g_position.y += g_velocity.y*deltaTime;
	}

	void Render() {

	}

	std::string StringOutputType() {
		return "Component<TransformComponent>";
	}
};

#endif