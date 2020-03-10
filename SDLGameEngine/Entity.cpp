#include "Entity.h"

Entity::Entity(EntityManager& manager) : g_entityManager(manager) {
	m_isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name, RenderLayer layer) : g_entityManager(manager), m_name(name), g_layer(layer) {
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


// The nature of the TypeMap is such that it will only return one entry when there are two components of the same type. This is potentially a problem if, e.g., two components of same type added by mistake and it creates a problem.
void Entity::ListAllComponents() const {

	for (auto& component : m_componentTypeMap) {
		std::cout << "	" << component.first->name() << "\n";
	}

	/*
	for (auto& component : m_components) {
		componentList += "	" + component->StringOutputType() + "\n";
	}*/

	return;
}