#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include "Component.h"
#include "Constants.h"
#include <vector>
#include <string>

class ColliderComponent;							

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
	Entity& AddEntity(std::string entityName, RenderLayer layer);
	std::vector<Entity*> GetEntities() const;
	std::vector<Entity*> GetEntitiesByLayer(RenderLayer layer) const;
	std::string CheckAllCollisions() const;
	void CheckCollisionType(ColliderComponent*, ColliderComponent*) const;
	unsigned int GetEntityCount();
	void ListAllEntities() const;
};

#endif
