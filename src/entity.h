/**********************************************************************************************//**
 * @file	src\entity.h
 *
 * @brief	Declares the entity class.  Used for all in-game that act and can be acted on.
 **************************************************************************************************/
#include <chipmunk.h> // needed or else cp things become undefined

#ifndef _ENTITY_
#define _ENTITY_

#define MAX_ENTITIES  255 /* Abs. max. # of entities that can be made in-game before I set fire to the rain. */

#define ENT_SHOW	0x00000001
#define ENT_THINK	0x00000002
#define ENT_SOLID	0x00000004
#define ENT_FJEKYL	0x00000008 // for sprites that show if you are in jekyll form
#define ENT_FHYDE	0x00000010 // for sprites that show if you've transformed to hyde

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
	PL_IDLE,
	PL_LEFT,
	PL_RIGHT,
	SIL_IDLE,
	KID_IDLE,
	BOS1_IDLE
};

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
	/** @brief	Trigger - for triggering think functions **/
	SDL_Rect		trigger;
	/** @brief	Sprite - The entity's new sprite. */
	sprite_t		*sprite;
	/** @brief	State of the animation. Might change to just state */
	int				animState;
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
	/** **/
	char			mode[10];
	/** @brief	Used incorrectly, might be depreciated. Amount of time before doing a specified statement. */
	int				thinkflags;
	/** @brief	Used for state machines; different things happen depending on the number it is set to.  Array of 20 integers gives ability to have multiple things set, might lower to 10. */
	int				thinknums[20];
	/** @brief	The class name of the entity. */
	char			classname[25];
	/** @brief	The type of the entity. */
	char			classType[10];
	/** @brief	The entity's current health. */
	float			currentHealth;
	/** @brief	The maximum health the entity could have. */
	int				max_health;
	/** @brief	The entity's current anger rate. */
	float			currentAnger;
	/** @brief	The maximum amt. of anger the entity could have. */
	int				maxAnger;

	// chipmunk
	cpBody * body;
	cpShape * shape;

	struct entity_s	*owner; 

	void			(*input)(struct entity_s *ent);
	void			(*move)(struct entity_s *ent);
	void			(*show)(struct entity_s *ent);

	void			(*setCamera)(void);

	void			(*think) (struct entity_s *self);
	void			(*touch) (struct entity_s *self);

} entity_t;

// for initialization/removal of entities
entity_t *initEnt (void);
void freeEnt (entity_t * self);
void initEntities ();
void closeEntities ();

// calling entity funcs
void EntityAlive ();
void entityShowAll (); // shows all entities, this is for debugging
void entityShowSwitch (); // shows entities based on level state
void entitySolidSwitch (); // makes entities solid based on level state

// collision detection - all three functions may be fused soon
void CheckCollisions ();
void CheckCollision (entity_t *ent, entity_t *targ, int max);
bool isCollide (entity_t *otherent, entity_t *ent);

// setting up the player
entity_t* getPlayer (void);
void initPlayer ();

// the player
void PlayerAlive (entity_t * ent);
//void playerInput ( entity_t *ent );
void move ( entity_t *ent );
void show ( entity_t *ent ); // show frames from a spritesheet... terribly

// all other ents
void showEnt ( entity_t *ent ); //  function for showing single sprite

/* thinks */
void projThink (entity_t *ent);
void alphaThink (entity_t *self);
void betaThink (entity_t *self);
void gammaThink (entity_t *self);
void kidSpawnThink (entity_t * self);
void bombSpawnThink (entity_t * self);
void bossThink (entity_t *self);
void particleMove (entity_t * self);
void emitterThink (entity_t * self);

/* setting the entity states */
void setStateTo (entity_t *ent, int animState);

#endif