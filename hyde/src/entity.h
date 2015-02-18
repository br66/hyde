#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"


#define MAX_ENTITIES  255

typedef struct entity_s
{
	int		inuse;
	int		clipmask;

	int		x,y;
	int		xVel, yVel;

	int		health;
	int		max_health;

	Sprite	*sprite;

	int		deadflag;

} entity_t;

entity_t listEntities[MAX_ENTITIES];
int max_ents;


entity_t *Init_Ent (void);	// adds entity into memory ????
void (*think)(entity_t *self);	// entity actions for every frame, needs to be given a think function to work
void Free_Ent(entity_t *self);	// removes entity to free up memory

void player_die (entity_t *self);