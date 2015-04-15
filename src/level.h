/**********************************************************************************************//**
 * @file	src\level.h
 *
 * @brief	Declares the level class. Due to lack of organization and successful implementation of 
 * 			YAML, this class will be removed.
 **************************************************************************************************/

#ifndef _LEVEL_
#define _LEVEL_

typedef struct level_s
{
	char			level[100];
	void			(*start)(struct level_s *level); //will show level stuff

	SDL_Surface		*backgrounds[20];
	entity_t		*lvlEntities[20];
}level_t;

void show_LevelOne();
void show_LevelTwo();

//level_t levels[10];

#endif