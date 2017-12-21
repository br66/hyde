/**********************************************************************************************//**
 * @file	Component.hpp
 * @author	br66
 * @date	6/26/17
 * @brief	
 **************************************************************************************************/

#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

class Entity; // Entity class is needed here, tell compiler that entity class will exist early so I can use it now

class Component
{
public:
	Component();
	Component(Entity* entity); // << forgets difference between using pointer and reference here
	~Component();

public:
	bool Active();

	virtual void Update() = 0;

private:
	Entity* m_parent; /** Entity that owns this component */
	bool m_active;  /** Is this component in use? */
};

#endif