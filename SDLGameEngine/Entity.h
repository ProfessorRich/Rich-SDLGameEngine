#ifndef ENTITY_H
#define ENTITY_H

#include "EntityManager.h"
#include "Component.h"
#include <vector>
#include <string>
#include <map>

// So this compiles...
class EntityManager;
class Component;

class Entity {
private:
	EntityManager& g_entityManager;
	bool m_isActive;
	std::vector<Component*> m_components;
	std::string m_name;
	std::map<const std::type_info*, Component*> m_componentTypeMap;

public:
	std::string GetName();
	Entity(EntityManager& manager);
	Entity(EntityManager& manager, std::string name);
	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const;
	void ListAllComponents() const;

	// I don't really understand template syntax... but the idea here is that whatever type of component is 'added' by AddComponent, this will deal with it.
	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->g_owner = this;
		m_components.emplace_back(newComponent);
		m_componentTypeMap[&typeid(*newComponent)] = newComponent;
		newComponent->Initialise();
		return *newComponent;
	}

	template <typename T>
	T* GetComponent() {
		return static_cast<T*>(m_componentTypeMap[&typeid(T)]);					// so ugly and very hard to understand. It gets the component typeid from the map.
	}

	template <typename T>
	bool HasComponent() const {
		bool found = false;
		for (auto& component : m_componentTypeMap) {
			if (&typeid(T) == component.first) found = true;
		}
		return found;
	}

};

#endif