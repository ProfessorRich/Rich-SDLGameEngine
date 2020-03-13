#ifndef SPAWNERCOMPONENT_H
#define SPAWNERCOMPONENT_H

// I don't really like this one AT ALL.

#include <glm.hpp>
#include <iostream>

#include "EntityManager.h"
#include "TransformComponent.h"
#include "ProjectileComponent.h"

extern EntityManager g_entityManager;

class SpawnerComponent : public Component {
private:
	TransformComponent* m_transform;
	int m_spawnSpeed;
	float m_spawnAngle;
	int m_range, m_projectileWidth, m_projectileHeight;
	bool m_shouldItLoop; 
	std::string m_projectileTextureId;
	 
public:
	SpawnerComponent(int spawnAngleInDegrees, int spawnSpeed, int range, bool shouldItLoop, int projectileWidth, int projectileHeight, std::string projectileTextureId) {
		m_spawnAngle = spawnAngleInDegrees;
		m_spawnSpeed = spawnSpeed;
		m_range = range;
		m_projectileWidth = projectileWidth;
		m_projectileHeight = projectileHeight;
		m_shouldItLoop = shouldItLoop;
		m_projectileTextureId = projectileTextureId;
	}

	void Initialise() override {
		m_transform = g_owner->GetComponent<TransformComponent>();

		Entity& newProjectile = g_entityManager.AddEntity("projectile", G_PROJECTILE_LAYER);

		newProjectile.AddComponent<TransformComponent>(
			static_cast<int>((m_transform->g_position.x) + (m_transform->g_width / 2)),
			static_cast<int>((m_transform->g_position.y) + (m_transform->g_height / 2)),
			static_cast<int>(glm::cos(m_spawnAngle) * m_spawnSpeed),
			static_cast<int>(glm::sin(m_spawnAngle) * m_spawnSpeed),
			static_cast<int>(m_projectileWidth),
			static_cast<int>(m_projectileHeight),
			1 // projectile SCALE is not implemented - TODO
			);
		newProjectile.AddComponent<SpriteComponent>(m_projectileTextureId);
		newProjectile.AddComponent<ProjectileComponent>(m_spawnAngle, m_spawnSpeed, m_range, m_shouldItLoop);
	}

	void Update(float deltaTime) override {

	}
};

#endif 

