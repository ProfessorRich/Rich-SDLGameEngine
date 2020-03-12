#include <iostream>

#include "EntityManager.h"
#include "ColliderComponent.h"
#include "Collision.h"


void EntityManager::ClearData() {
	for (auto& entity : m_entities) {
		entity->Destroy();
	}
}

EntityManager::EntityManager() {
}

void EntityManager::Update(float deltaTime) {		//TODO - is this working OK??
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		if (!m_entities.at(i)->IsActive()) {
			m_entities.erase(m_entities.begin() + i);
		}
		else {
			m_entities.at(i)->Update(deltaTime);
		}
	}
}

void EntityManager::Render() const {
	for (int i = 0; i < G_NUM_RENDER_LAYERS; i++) {
		for (auto& entity : GetEntitiesByLayer(static_cast<RenderLayer>(i))) {
			entity->Render();
		}
	}
}

void EntityManager::Destroy() {
	for (auto& entity : m_entities) {
		entity->Destroy();
	}
}

bool EntityManager::HasNoEntities() const
{
	return m_entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName, RenderLayer layer) {
	Entity* entity = new Entity(*this, entityName, layer);
	m_entities.emplace_back(entity);

	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
	return m_entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(RenderLayer layer) const
{
	std::vector<Entity*> entitiesByLayer;

	for (auto& entity : m_entities) {
		if (entity->g_layer == layer) {
			entitiesByLayer.emplace_back(entity);
		}
	}
	return entitiesByLayer;
}

// The function to check all collisions... might be horribly inefficient?
std::string EntityManager::CheckAllCollisions() const {
	
	if (m_entities.size() < 2) {
		return std::string();
	}
	else {
		for (unsigned int i = 0; i < (m_entities.size() - 1); i++) {																	// -1 as last element will have already been checked against all others
			if (m_entities.at(i)->HasComponent<ColliderComponent>()) {																	// Is it a collider?
				ColliderComponent* thisCollider = m_entities.at(i)->GetComponent<ColliderComponent>();
				for (unsigned int j = (i + 1); j < m_entities.size(); j++) {														// No -1 as the j loop DOES need to check even the last element.
					if (m_entities.at(j)->HasComponent<ColliderComponent>()) {
						ColliderComponent* thatCollider = m_entities.at(j)->GetComponent<ColliderComponent>();
						if (Collision::CheckRectangleCollision(thisCollider->g_hitBox, thatCollider->g_hitBox)) {
							CheckCollisionType(thisCollider, thatCollider);
						}
					}
				}
			}
		}
	}
	return std::string();
}

void EntityManager::CheckCollisionType(ColliderComponent* thisCollider, ColliderComponent* thatCollider) const {
	if (G_DEBUG) {
		std::cout << thisCollider->g_colliderTag << " has collided with " << thatCollider->g_colliderTag << std::endl;
	}
}

unsigned int EntityManager::GetEntityCount() const
{
	return m_entities.size();
}

void EntityManager::ListAllEntities() const {
	for (auto& entity : m_entities) {
		std::cout << "Entity Name: " << entity->GetName() << std::endl;
		entity->ListAllComponents();
		std::cout << std::endl;
	}
}