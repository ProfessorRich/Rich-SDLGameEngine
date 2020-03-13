#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H

#include <glm.hpp>

#include "EntityManager.h"
#include "TransformComponent.h"
#include <iostream>

class ProjectileComponent : public Component {
private:
	TransformComponent* m_transform;
	glm::vec2 m_origin;
	int m_spawnSpeed;
	float m_spawnAngle;
	int m_range;
	bool m_shouldItLoop;

public:
	ProjectileComponent(int spawnAngleInDegrees, int spawnSpeed, int range, bool shouldItLoop) {
		m_spawnAngle = glm::radians(static_cast<float>(spawnAngleInDegrees));
		m_spawnSpeed = spawnSpeed;
		m_range = range;
		m_shouldItLoop = shouldItLoop;
	}

	void Initialise() override {
		m_transform = g_owner->GetComponent<TransformComponent>();
		m_origin = glm::vec2(m_transform->g_position.x, m_transform->g_position.y);

		std::cout << m_origin.x << m_origin.y << " " << m_spawnSpeed << " " << m_spawnAngle << " " << m_range << " " << m_shouldItLoop << std::endl;
		std::cout << g_owner->GetComponent<TransformComponent>()->g_position.x << " " << g_owner->GetComponent<TransformComponent>()->g_velocity.x << std::endl;
	}

	void Update(float deltaTime) override {
		if (glm::distance(m_transform->g_position, m_origin) > m_range) {
			if (m_shouldItLoop) {
				m_transform->g_position = m_origin;
			}
			else {
				g_owner->Destroy();
			}
		}
	}
};

#endif 
