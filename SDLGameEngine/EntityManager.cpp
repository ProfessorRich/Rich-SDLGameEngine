#include "EntityManager.h"
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