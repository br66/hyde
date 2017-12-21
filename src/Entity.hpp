/**********************************************************************************************//**
 * @file	entity.hpp
 * @author	br66
 * @date	5/29/17
 * @brief	Describes what makes up an Entity (element within game that acts and/or is acted upon).
 **************************************************************************************************/

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "Component.hpp"

/**********************************************************************************************//**
 * @class	Entity
 * @date	6/4/17
 * @brief	Base class for all in-game objects
 **************************************************************************************************/
class Entity
{
public:
	Entity();
	~Entity();

public:
	const std::string Name(); // returns direct read-only reference to name of the object
	void SetName(const std::string &name);

	bool Active(); // if active or not

	// Tag management
	int Tags();
	//bool IfUsingTag();
	//void AddTag();
	//void RemoveTag();
	//void RemoveAllTags();

	// Layer management
	int Layer();
	//int IfInLayer();
	//int PutInLayer();
	//void TakeOutofLayer();

	// Owner
	Entity* Owner(); // Returns owner // using pointer here because I would if I was using a linked list despite me not changing a property of the entity pointed to
	bool IfOwnerExists(); // Checks if the entity has an owner
	void SetOwner(Entity* entity); // Gives ownership of entity to another.

private:
	std::string m_name; /** name of Entity */

	bool m_active; // may change to enum

	int m_tags; // bitflags?????
	
	int m_layer;

	Entity *m_owner; /** very common for Entity to be child of another */

	std::vector<Component*> m_components;  // Entity-Component System.  Composition over inheritance, to avoid atrocities like Quake 4
};

#endif