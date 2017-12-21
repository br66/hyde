#include <vector>
#include <iostream>

#include "Entity.hpp"

Entity::Entity()
{
	m_name = "";
	m_active = 0;
	m_tags = 0;
	m_layer = 0;
	m_owner = NULL;
	
	std::vector<Component*>::iterator it = m_components.begin();
	while (it != m_components.end())
	{
		*it = NULL;
	}
}

Entity::~Entity()
{
	m_name = "";
	m_active = 0;
	m_tags = 0;
	m_layer = 0;
	m_owner = NULL;
	
	std::vector<Component*>::iterator it = m_components.begin();
	while (it != m_components.end())
	{
		*it = NULL;
	}
}

// not changing anything here
const std::string Entity::Name()
{
	return m_name;
}

bool Entity::Active()
{
	return m_active;
}

int Entity::Tags()
{
	return m_tags;
}

int Entity::Layer()
{
	return m_layer;
}

Entity* Entity::Owner()
{
	return m_owner;
}

bool Entity::IfOwnerExists()
{
	if (m_owner)
		return true;
	return false;
}

void Entity::SetOwner(Entity* entity)
{
	this->m_owner = entity;
}