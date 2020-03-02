#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include "Component.h"
#include <vector>
#include <string>

class EntityManager {
private:
	std::vector<Entity*> m_entities;

public:
	void ClearData();
	EntityManager();
	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool HasNoEntities();
	Entity& AddEntity(std::string entityName);
	std::vector<Entity*> GetEntities() const;
	unsigned int GetEntityCount();
	void ListAllEntities();
};

#endif
