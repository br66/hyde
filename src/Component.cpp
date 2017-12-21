#include <iostream>

#include "Component.hpp"

Component::Component()
{
	m_parent = NULL;
}

Component::Component(Entity* entity)
{
	m_parent = entity;
}

Component::~Component()
{
	m_parent = NULL;
}

bool Component::Active()
{
	return m_active;
}