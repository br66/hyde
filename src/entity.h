/* For this commit, include guards have been added for all header files except
assets.  Everything in assets is being gradually removed.  The MAX_ENTITIES and
max_ents is defined here as well as entity flags (ENT_SHOW) and macros to set, 
remove, and check flags.  PlayerAlive() lessens lines of code and call move,
show, and set camera functions.  PlayerProperties does what was in game.c which
was setting all of the player's variables.  getPlayer() returns player to lessen
amount of externs. */

#ifndef _ENTITY_
#define _ENTITY_

#define MAX_ENTITIES  255 /* Abs. max. # of entities that can be made in-game before I set fire to the rain. */

#define ENT_SHOW	0x00000001
#define ENT_THINK	0x00000002
#define ENT_SOLID	0x00000004

#define REMOVE_FLAG(x, y) (x &= ~y)
#define SET_FLAG(x, y) (x |= y)
#define IS_SET(x, y) (x & y)

int max_ents; /* Number of entities that have been made in-game */

/**********************************************************************************************//**
 * @typedef	struct entity_s
 *
 * @brief	Defines an structure representing an entity.
 **************************************************************************************************/

typedef struct entity_s
{
	/** @brief	The inuse. */
	int				inuse;

	/**********************************************************************************************//**
	 * @property	float x,y
	 *
	 * @brief	Gets the y coordinate.
	 *
	 * @return	The y coordinate.
	 **************************************************************************************************/

	float			x,y;
	float			xVel, yVel;

	/** @brief	The box. */
	SDL_Rect		bBox;
	SDL_Rect		fill;

	/** @brief	The sprite. */
	SDL_Surface		*sprite;
	int				framesperline;

	/** @brief	The width. */
	int				width;
	int				height;
	/** @brief	The projectiles. */
	int				projectiles;

	/** @brief	true if on ground. */
	bool			onGround;

	/** @brief	The next time to think. */
	Uint32			nextThink;

	int				flags;
	int				thinkflags;
	int				thinknums[20];

	/** @brief	The solid. */
	int				solid;

	/** @brief	The classname. */
	char			classname[25];

	int					currentHealth;
	int					max_health;

	//int				deadflag;

	/**********************************************************************************************//**
	 * @struct	entity_s*
	 *
	 * @brief	The entity that owns this one.
	 *
	 * @author	iwh
	 * @date	3/24/2015
	 **************************************************************************************************/

	struct entity_s	*owner; 

	void			(*resetPosition) (struct entity_s *ent);
	void			(*handle_Input)(struct entity_s *ent);
	void			(*move)(struct entity_s *ent);
	void			(*show)(struct entity_s *ent);

	void			(*setCamera)(void);

	void			(*think) (struct entity_s *self);
	void			(*touch) (struct entity_s *self);

} entity_t;


entity_t *Init_Ent (void);
void Free_Ent(entity_t *self);
void EntityAlive ();
void EntityShow ();
void CheckCollisions ();
void CheckCollision (entity_t *ent, entity_t *targ, int max);

void PlayerAlive ();

void init_Position( entity_t *ent );
void handle_Input( entity_t *ent );
void move( entity_t *ent );
void show( entity_t *ent );
void show_Ent( entity_t *ent );

/* technical */
void set_Camera( entity_t *ent);
bool isCollide (entity_t *otherent, entity_t *ent);

/* thinks */
void projThink (entity_t *ent);
void alphaThink (entity_t *self);
void betaThink (entity_t *self);
void gammaThink (entity_t *self);
void bossThink (entity_t *self);

/* for the player */
void playerProperties(entity_t *player);
entity_t* getPlayer(void);

#endif