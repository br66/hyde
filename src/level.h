/**********************************************************************************************//**
 * @file	src\level.h
 *
 * @brief	Declares the level class. Due to lack of organization and successful implementation of 
 * 			JSON, this class will be removed and replaced with JSON keys and values.
 **************************************************************************************************/

#ifndef _LEVEL_
#define _LEVEL_

typedef struct level_s
{
	char			level[50];

	sprite_t		*backgrounds[10];
	entity_t		*lvlEntities[20];

}level_t;

void show_LevelOne();
void show_LevelTwo();

#endif