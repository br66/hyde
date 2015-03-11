#include <SDL.h>
#include "boolean.h" // WTF

#define MAX_ENTITIES  255 //max number that can be created
int max_ents; //max number of ents that have been created in game

typedef struct entity_s
{
	int				inuse;

	int				x,y;
	int				xVel, yVel;

	SDL_Rect		bBox;

	SDL_Surface		*sprite;

	int				width;
	int				height;

	bool			onGround;

	//int				health;
	//int				max_health;

	//int				deadflag;

	void			(*resetPosition) (struct entity_s *ent);
	void			(*handle_Input)(struct entity_s *ent);
	void			(*move)(struct entity_s *ent);
	void			(*show)(struct entity_s *ent);

	void			(*setCamera)(void);
} entity_t;

entity_t listEntities [MAX_ENTITIES];

/* create/remove entity */
entity_t *Init_Ent (void);		// adds entity into memory
void (*think)(entity_t *self);	// *NEW* entity actions for every frame
void Free_Ent(entity_t *self);	// entity is ready to be replaced

/* edit entity */
void reset_Position( entity_t *ent );
void handle_Input( entity_t *ent );
void move( entity_t *ent );
void show( entity_t *ent );
void show_Enemy( entity_t *ent );

/* technical */
void set_Camera( entity_t *ent);
bool check_Col (SDL_Rect A, SDL_Rect B);