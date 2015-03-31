
/* Absolute maximum number of entities that can be made in-game before I set fire to the rain. */
#define MAX_ENTITIES  255

/* Number of entities that have been made in-game */
int max_ents;

/**********************************************************************************************//**
 * @typedef	struct entity_s
 *
 * @brief	Defines an alias representing the entity s.
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

	/** @brief	The width. */
	int				width;
	int				height;
	/** @brief	The projectiles. */
	int				projectiles;

	/** @brief	true to on ground. */
	bool			onGround;

	/** @brief	The next think. */
	Uint32			nextThink;

	int				flags;
	int				thinkflags;
	int				thinknums[20];

	/** @brief	The solid. */
	int				solid;

	/** @brief	The classname[ 25]. */
	char			classname[25];

	//int				health;
	//int				max_health;

	//int				deadflag;

	/**********************************************************************************************//**
	 * @struct	entity_s*
	 *
	 * @brief	The entity that owns.
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

/* The list of all the entities using memory */
entity_t listEntities [MAX_ENTITIES];

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