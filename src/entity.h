/**********************************************************************************************//**
 * @file	src\entity.h
 *
 * @brief	Declares the entity class.  Used for all in-game that act and can be acted on.
 **************************************************************************************************/

#ifndef _ENTITY_
#define _ENTITY_

#define MAX_ENTITIES  50 /* Abs. max. # of entities that can be made in-game before I set fire to the rain. */

#define ENT_SHOW	0x00000001
#define ENT_THINK	0x00000002
#define ENT_SOLID	0x00000004

#define REMOVE_FLAG(x, y) (x &= ~y)
#define SET_FLAG(x, y) (x |= y)
#define IS_SET(x, y) (x & y)

/**********************************************************************************************//**
 * @enum	animState
 *
 * @brief	Values that represent animation states for entity, might move new animation header.
 **************************************************************************************************/
enum animState
{
	ANIM_IDLE,
	ANIM_WLEFT,
	ANIM_WRIGHT
};

int max_ents; /* Number of entities that have been made in-game */

/**********************************************************************************************//**
 * @typedef	struct entity_s
 *
 * @brief	Defines an structure representing an entity.
 **************************************************************************************************/
typedef struct entity_s
{
	/** @brief	Inuse - for checking if the entity is being used. */
	int				inuse;

	float			x,y;
	float			xVel, yVel;

	/** @brief	Bounding Box - for collision */
	SDL_Rect		bBox;
	/** @brief	Will be removed. */
	SDL_Rect		fill;
	/** @brief	The entity's sprite. */
	SDL_Surface		*sprite;
	/** @brief	The amount of frames each line the spritesheet has if the entity's sprite is a spritesheet. */
	int				framesperline;
	/** @brief	The entity sprite's current frame. */
	int				frame;
	/** @brief	State of the animation. */
	int				animState;
	/** @brief	Amount of time before moving to the next frame. */
	int				animThink;
	/** @brief	Entity's width. */
	int				width;
	/** @brief	Entity's height. */
	int				height;
	/** @brief	Boolean that is true if the entity is on the ground. */
	bool			onGround;
	/** @brief	Amount of time before calling the think function again. */
	Uint32			nextThink;
	/** @brief	The flags that turn on and off entities' functions. */
	int				flags;
	/** @brief	Used incorrectly, might be depreciated. Amount of time before doing a specified statement. */
	int				thinkflags;
	/** @brief	Used for state machines; different things happen depending on the number it is set to.  Array of 20 integers gives ability to have multiple things set, might lower to 10. */
	int				thinknums[20];
	/** @brief	The classname of the entity. */
	char			classname[25];
	/** @brief	The entity's current health. */
	int				currentHealth;
	/** @brief	The maximum health the entity could have. */
	int				max_health;
	/** @brief	The entity's current anger rate. */
	int				currentAnger;
	/** @brief	The maximum amt. of anger the entity could have. */
	int				maxAnger;

	/**********************************************************************************************//**
	 * @struct	entity_s*
	 *
	 * @brief	The entity that owns this one.
	 *
	 * @author	iwh
	 * @date	3/24/2015
	 **************************************************************************************************/

	struct entity_s	*owner; 

	void			(*handle_Input)(struct entity_s *ent);
	void			(*move)(struct entity_s *ent);
	void			(*show)(struct entity_s *ent);

	void			(*setCamera)(void);

	void			(*think) (struct entity_s *self);
	void			(*touch) (struct entity_s *self);

} entity_t;

//UNORGAINIZED
entity_t *Init_Ent (void);
void Free_Ent(entity_t *self);

void EntityAlive ();
void EntityShow ();

void CheckCollisions ();
void CheckCollision (entity_t *ent, entity_t *targ, int max);

void PlayerAlive ();

void handle_Input( entity_t *ent );
void move( entity_t *ent );
void show( entity_t *ent ); // show frames from a spritesheet
void show_Ent( entity_t *ent ); // placeholder function for merely showing single sprite
//--------------------------------------

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

/* setting states */
void setStateTo(entity_t *ent, int animState);

#endif