#define MAX_ENTITIES  255 //max number that can be created
int max_ents; //max number of ents that have been created in game

typedef struct entity_s
{
	int				inuse;

	float			x,y;
	float			xVel, yVel;

	SDL_Rect		bBox;

	SDL_Surface		*sprite;

	int				width;
	int				height;
	int				projectiles;

	bool			onGround;

	Uint32			nextThink;

	int				flags;
	int				thinkflags;
	int				thinknums[20];

	int				solid;

	//int				health;
	//int				max_health;

	//int				deadflag;
	struct entity_s	*owner;

	void			(*resetPosition) (struct entity_s *ent);
	void			(*handle_Input)(struct entity_s *ent);
	void			(*move)(struct entity_s *ent);
	void			(*show)(struct entity_s *ent);

	void			(*setCamera)(void);

	void			(*think) (struct entity_s *self);
	void			(*touch) (struct entity_s *self);

} entity_t;

entity_t listEntities [MAX_ENTITIES];

/* create/remove entity */
entity_t *Init_Ent (void);		// adds entity into memory
void Free_Ent(entity_t *self);	// entity is ready to be replaced
void EntityAlive ();			// calls all think functions
void EntityShow();
void CheckCollisions();
void CheckCollision(entity_t *ent);

/* edit entity */
void init_Position( entity_t *ent );
void handle_Input( entity_t *ent );
void move( entity_t *ent );
void show( entity_t *ent );
void show_Enemy( entity_t *ent );
void show_Relative (entity_t *ent);

/* technical */
void set_Camera( entity_t *ent);
bool isCollide (entity_t *otherent, entity_t *ent);

/* thinks */
void projThink (entity_t *ent);
void alphaThink (entity_t *self);
void betaThink (entity_t *self);
void gammaThink (entity_t *self);
void bossThink (entity_t *self);
void wallThink (entity_t *self);