#include "EntityManager.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include <iostream>

void EntityManager::ClearData() {
	for (auto& entity : m_entities) {
		entity->Destroy();
	}
}

EntityManager::EntityManager() {
}

void EntityManager::Update(float deltaTime) {
	for (auto& entity : m_entities) {
		entity->Update(deltaTime);
	}
}

void EntityManager::Render() {
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

bool EntityManager::HasNoEntities()
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
std::string EntityManager::CheckAllCollisions() {
	
	for (unsigned int i = 0; i < (m_entities.size()-1); i++) {																	// -1 as last element will have already been checked against all others
		if (m_entities[i]->HasComponent<ColliderComponent>()) {															// Is it a collider?
			for (unsigned int j = (i + 1); j < (m_entities.size() - 1); j++) {
				if (m_entities[j]->HasComponent<ColliderComponent>()) {			
					if (Collision::CheckRectangleCollision(m_entities[i]->GetComponent<ColliderComponent>()->g_hitBox, m_entities[j]->GetComponent<ColliderComponent>()->g_hitBox)) {
						std::cout << m_entities[i]->GetName() << " has collided with " << m_entities[j]->GetName() << std::endl;
					}
				}
			}
		}
	}
	return std::string();
}

unsigned int EntityManager::GetEntityCount()
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