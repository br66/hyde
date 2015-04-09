/* Nothing changed here except
include guards (#ifndef). */

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

/* lvl/stage 1 specific entities */
entity_t *platform1;
entity_t *platform2;
entity_t *platform3;
entity_t *platform4;
/* lvl/stage 2 specific entities */
entity_t *platformA1;
entity_t *platformA2;
entity_t *platformA3;
entity_t *platformA4;

level_t levels[10];

#endif