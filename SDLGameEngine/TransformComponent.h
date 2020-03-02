#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "EntityManager.h"
#include "Game.h"
#include "glm.hpp"
#include <SDL.h>
#include <iostream>

class TransformComponent : public Component {
public:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	int m_width;
	int m_height;
	int m_scale;

	TransformComponent(int posX, int posY, int velX, int velY, int width, int height, int scale) {
		m_position = glm::vec2(posX, posY);
		m_velocity = glm::vec2(velX, velY);
		m_width = width;
		m_height = height;
		m_scale = scale;
	}

	void Initialise() {
	}

	void Update(float deltaTime) {
		m_position.x += m_velocity.x*deltaTime;
		m_position.y += m_velocity.y*deltaTime;
	}

	void Render() {
		SDL_Rect transformRect = {
			(int)m_position.x,
			(int)m_position.y,
			m_width * m_scale,
			m_height * m_scale
		};

		SDL_SetRenderDrawColor(Game::g_renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(Game::g_renderer, &transformRect);
	}

	std::string GetType() {
		return "Component<TransformComponent>";
	}
};

#endif