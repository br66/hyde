#include "SDL.h"

#define MAX_ENTITIES  255 //max number that can be created
int max_ents; //max number of ents that have been created in game

typedef struct entity_s
{
	int		inuse;

	int		x,y;
	int		xVel, yVel;

	int		width;
	int		height;

	int		health;
	int		max_health;

	int		deadflag;

	void	(*resetPosition) (struct entity_s *ent);
	void	(*handle_Input)(struct entity_s *ent);
	void	(*move)(struct entity_s *ent);
	void	(*show)(struct entity_s *ent);

} entity_t;

entity_t listEntities [MAX_ENTITIES];

entity_t *Init_Ent (void);	// adds entity into memory
//void (*think)(entity_t *self);	// entity actions for every frame, needs to be given a think function to work
void Free_Ent(entity_t *self);	// entity is ready to be replaced

void reset_Position( entity_t *ent );
void handle_Input( entity_t *ent );
void move( entity_t *ent );
void show( entity_t *ent );