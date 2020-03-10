#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <string>

#include "Entity.h"
#include "Component.h"
#include "Constants.h"

class ColliderComponent;							

class EntityManager {
private:
	std::vector<Entity*> m_entities;

public:
	void ClearData();
	EntityManager();
	void Update(float deltaTime);
	void Render() const;
	void Destroy();
	bool HasNoEntities() const;
	Entity& AddEntity(std::string entityName, RenderLayer layer);
	std::vector<Entity*> GetEntities() const;
	std::vector<Entity*> GetEntitiesByLayer(RenderLayer layer) const;
	std::string CheckAllCollisions() const;
	void CheckCollisionType(ColliderComponent*, ColliderComponent*) const;
	unsigned int GetEntityCount() const;
	void ListAllEntities() const;
};

#endif
