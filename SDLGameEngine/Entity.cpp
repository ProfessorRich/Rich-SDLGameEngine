#include "Entity.h"

Entity::Entity(EntityManager& manager) : g_entityManager(manager) {
	m_isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name) : g_entityManager(manager), m_name(name) {
	m_isActive = true;
}

void Entity::Update(float deltaTime) {
	for (auto& component : m_components) {
		component->Update(deltaTime);
	}
}

void Entity::Render() {
	for (auto& component : m_components) {
		component->Render();
	}
}

void Entity::Destroy() {
	m_isActive = false;
}

bool Entity::IsActive() const {
	return m_isActive;
}

std::string Entity::GetName() {
	return m_name;
}

std::string Entity::ListAllComponents() {
	std::string componentList;

	for (auto& component : m_components) {
		componentList += "	" + component->StringOutputType() + "\n";
	}

	return componentList;
}