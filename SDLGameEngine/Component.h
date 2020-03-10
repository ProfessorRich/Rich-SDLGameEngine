#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>

#include "Entity.h"

// holder class so that this can compile and then Entity and EntityManager can compile after this!
class Entity;	

class Component {
public:
	Entity* g_owner;

	virtual ~Component() {}
	virtual void Initialise() {}
	virtual void Update(float deltaTime) {}
	virtual void Render() {}
	
	/*
	virtual std::string StringOutputType() {
		return "Component<UNKNOWN>";
	}*/
};

#endif