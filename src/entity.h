/**********************************************************************************************//**
 * @file	entity.h
 *
 * @brief	This is the entity class.  Used for all in-game that act and can be acted on.  <<< Redefine
 **************************************************************************************************/

#ifndef _ENTITY_H_
#define _ENTITY_H_

 // Standard C headers
#include <string.h> 

 // Third-party library headers
#include <chipmunk.h>

 // Custom headers
#include "sprite.h"

// math related math.h
typedef struct
{
	float x, y;
}Vector2D;

// math related
typedef struct
{
	float x, y, z;
}Vector3D;

struct Transform
{
	Vector3D m_position;
	Vector3D m_rotation;
	Vector3D m_scale;
};

struct Collider
{
	// box or circle collider
	int m_type;

	// shape determined by type
	cpShape *m_shape;
};

struct Physics
{
	cpBody *m_body;
};

struct Health
{
	int m_health;
};

/*
	Defining a new data type, not using typedef.
	Using typedef hides the data type (which in this case is struct)
	Hiding data types is no good, unless necessary.
	Not really necessary here.
*/
/*
	Entity should control size of Sprite via transform
*/
struct Entity
{
	// name of Entity
	char m_name[36];

	// whether the Entity is being used in computer memory (0 if yes, 1 if no)
	int m_active;

	// will use for multiple tags like Unity (name bittags???)
	int m_tags;

	// layers for visiblilty like Unity
	int m_layer;

	// Position, Rotation, Scale
	struct Transform *m_transform;

	// for getting collision information
	struct Collider *m_collider;

	// for having um... physics
	struct Physics *m_physics;

	// made a health component
	struct Health *m_health;

	// see you can see the damn object
	struct Sprite *m_sprite;

	// this entity could be the child of another
	struct Entity *m_owner;
};

// creation of one
struct Entity *NewEntity();
void DeleteEntity(struct Entity *self);

// creation of many
void EntityMInit();
void EntityMDel();

int MaxRecordedEntities();






















/*

//Maximum # of entities that can exist at once. 

#define MAX_ENTITIES  255

//	Flags
#define ENT_SHOW	0x00000001
#define ENT_THINK	0x00000002
#define ENT_SOLID	0x00000004
#define ENT_FJEKYL	0x00000008 // remoooooooooove
#define ENT_FHYDE	0x00000010 // remoooooooooove

//	Flag settings
#define REMOVE_FLAG(x, y) (x &= ~y)
#define SET_FLAG(x, y) (x |= y)
#define IS_SET(x, y) (x & y)

/**********************************************************************************************//**
 * @enum	animState
 *
 * @brief	Values that represent animation states for entity, might move new animation header.
 **************************************************************************************************/
/*enum animState
{
	PL_IDLE,
	PL_LEFT,
	PL_RIGHT,
	SIL_IDLE,
	KID_IDLE,
	BOS1_IDLE
};

************************************************************************************************
 * @typedef	struct entity_s
 *
 * @brief	Defines an structure representing an entity.
 **************************************************************************************************
typedef struct entity_s
{
	@brief	Inuse - for checking if the entity is being used. 
	int				inuse;

	// TransformComponent transform; // will have position, rotation and scale vectors

	float			x,y; // DEPRECATION INCOMING
	float			xVel, yVel; // DEPRECATION INCOMING

	// PhysicsComponent physics; // bounding box, bounding shape

	// SpriteComponent sprite;

	// AnimationComponent anim;

	 @brief	Bounding Box - for collision 
	SDL_Rect		bBox; // DEPRECATION INCOMING
	 @brief	Trigger - for triggering think functions
	SDL_Rect		trigger;
	 @brief	Sprite - The entity's new sprite.
	sprite_t		*sprite;
	@brief	State of the animation. Might change to just state
	int				animState;
	 @brief	Entity's width. 
	int				width;
	 @brief	Entity's height. 
	int				height;
	 @brief	Boolean that is true if the entity is on the ground. 
	bool			onGround;
	 @brief	Amount of time before calling the think function again. 
	Uint32			nextThink;
	@brief	The flags that turn on and off entities' functions. 
	int				flags;
	char			mode[10];
	 @brief	Used incorrectly, might be depreciated. Amount of time before doing a specified statement.
	int				thinkflags;
	 @brief	Used for state machines; different things happen depending on the number it is set to.  Array of 20 integers gives ability to have multiple things set, might lower to 10. 
	int				thinknums[20];
	 @brief	The class name of the entity.
	char			classname[25];
	 @brief	The type of the entity. 
	char			classType[10];
	 @brief	The entity's current health. 
	float			currentHealth;
	 @brief	The maximum health the entity could have. 
	int				max_health;
	 @brief	The entity's current anger rate. 
	float			currentAnger;
	 @brief	The maximum amt. of anger the entity could have. 
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

 thinks
void projThink (entity_t *ent);
void alphaThink (entity_t *self);
void betaThink (entity_t *self);
void gammaThink (entity_t *self);
void kidSpawnThink (entity_t * self);
void bombSpawnThink (entity_t * self);
void bossThink (entity_t *self);
void particleMove (entity_t * self);
void emitterThink (entity_t * self);

 setting the entity states 
void setStateTo (entity_t *ent, int animState);
*/
#endif