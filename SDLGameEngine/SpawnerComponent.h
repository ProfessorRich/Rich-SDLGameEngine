#ifndef SPAWNERCOMPONENT_H
#define SPAWNERCOMPONENT_H

// I don't really like this one AT ALL.

#include <glm.hpp>
#include "EntityManager.h"
#include "TransformComponent.h"

class SpawnerComponent : public Component {
private:
	TransformComponent* m_transform;
	glm::vec2 m_origin;
	int m_spawnSpeed;
	float m_spawnAngle;
	int m_range;
	bool m_shouldItLoop;

public:
	SpawnerComponent(int spawnAngleInDegrees, int spawnSpeed, int range, bool shouldItLoop) {
		m_spawnAngle = glm::radians(static_cast<float>(spawnAngleInDegrees));
		m_spawnSpeed = spawnSpeed;
		m_range = range;
		m_shouldItLoop = shouldItLoop;
	}

	void Initialise() override {
		m_transform = g_owner->GetComponent<TransformComponent>();
		m_origin = glm::vec2(m_transform->g_position.x, m_transform->g_position.y);

		m_transform->g_velocity = glm::vec2(glm::cos(m_spawnAngle) * m_spawnSpeed, glm::sin(m_spawnAngle) * m_spawnSpeed);
	}

	void Update(float deltaTime) override {
		if (glm::distance(m_transform->g_position, m_origin) > m_range) {
			if (m_shouldItLoop) {
				m_transform->g_position = m_origin;
			} else {
				g_owner->Destroy();
			}
		}	
	}
};

#endif 

