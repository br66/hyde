/**********************************************************************************************//**
 * @file	entity.c
 * @author	br66
 * @date	3/30/17
 * @brief	The entity source file is for defining the behavior for in-game elements that act and/or can be acted on.
 *			
 **************************************************************************************************/

// .c

// Custom headers
#include "boolean.h"
#include "entity.h"

// list of entities
struct Entity* _entityM = NULL;

int _entity_max_recorded = 0;
bool _entityMInitialized = 0; 

/**********************************************************************************************//**
 * @fn	void EntityAlive()
 *
 * @brief	Calls all entities' think function within limitations, then move to the next 
 *			entity in the array of entities.
 **************************************************************************************************/
/*void EntityAlive() 
{
	int i = 0;
	entity_t *e = listEntities;
	for (i = 0; i < MAX_ENTITIES; i++)
	{
		if (listEntities[i].inuse && listEntities[i].think)
		{
			if (listEntities[i].nextThink <= getCurrentTime())
				listEntities[i].think(&listEntities[i]);
				*/
			/*if listentiies[i].nextanimthink <= time
				call animthink; //replaced by show???*/
			
			/* for those without chipmunk physics
			if (e->xVel != 0)
				e->x += e->xVel;
			if (e->yVel != 0)
				e->y += e->yVel;

			// for those with chipmunk physics
			if (e->shape && e->body)
			{
				if (e->xVel != 0)
					//e->shape->body->p.x += e->xVel;
				//else
					//e->shape->body->v.x = 0;

				if (e->yVel != 0)
					//e->shape->body->p.y += e->yVel * 1.1;

				if (e->xVel > 1.2f)
					e->xVel = 1.2f;

				if (e->yVel > 2)
					e->yVel = 2;
			}
		}
		e++; // don't understand why I need this, w/out it only first entity can move (player)
	}
}
*/
/**********************************************************************************************//**
 * @fn	void entityShowAll ()
 *
 * @brief	Show all entities on screen that have a set show function.
 * @author	iwh
 **************************************************************************************************/
/*void entityShowAll ()
{
	int i = 0;
	entity_t *e = listEntities;
	for (i = 0; i < MAX_ENTITIES; i++)
	{
		if (listEntities[i].inuse)
		{
			//if (IS_SET(listEntities[i].flags, ENT_SHOW))
			//{
				if (listEntities[i].show != NULL)
				{
					(*listEntities[i].show)(&listEntities[i]);
				}
			//}
		}
		e++;
	}
}
*//*
void entityShowSwitch ()
{
	int i = 0;
	entity_t *e = listEntities;

	switch(Game.levelState)
	{
		case JEKYLL_MODE:
		{
			//printf("jekyll mode\n");
			for (i = 0; i < MAX_ENTITIES; i++)
			{
				if (listEntities[i].inuse > 0)
				{
					if(IS_SET(listEntities[i].flags, ENT_FHYDE))
						continue;

					if (IS_SET(listEntities[i].flags, ENT_FJEKYL) || IS_SET(listEntities[i].flags, ENT_SHOW))
					{
						if (listEntities[i].show != NULL)
						{
							(*listEntities[i].show)(&listEntities[i]);
						}
					}
				}
				e++;
			}
			break;
		}

		case HYDE_MODE:
		{
			//printf("hyde mode\n");
			for (i = 0; i < MAX_ENTITIES; i++)
			{
				if (listEntities[i].inuse > 0)
				{
					if(IS_SET(listEntities[i].flags, ENT_FJEKYL))
						continue;

					if (IS_SET(listEntities[i].flags, ENT_FHYDE ||  IS_SET(listEntities[i].flags, ENT_SHOW)))
					{
						if (listEntities[i].show != NULL)
						{
							(*listEntities[i].show)(&listEntities[i]);
						}
					}
				}
				e++;
			}
			break;
		}

		default:
				return; break;
	}
}
*//*
void entitySolidSwitch ()
{
	int i = 0;
	entity_t *list = listEntities;

	switch (Game.levelState)
	{
		case JEKYLL_MODE:
			{
				for (i = 0; i < MAX_ENTITIES; i++)
				{
					if(IS_SET(list[i].flags, ENT_FHYDE) && list[i].inuse > 0)
					{
						if (strcmp(list[i].classType, "enemy") == 0)
						{
							REMOVE_FLAG(list[i].flags, ENT_SOLID);
						}
					}
					
					if(IS_SET(list[i].flags, ENT_FJEKYL) && list[i].inuse > 0)
					{
						if (strcmp(list[i].classType, "enemy") == 0)
						{
							SET_FLAG(list[i].flags, ENT_SOLID);
						}
					}
				}
			}

		case HYDE_MODE:
			{
				for (i = 0; i < MAX_ENTITIES; i++)
				{
					if (!strcmp(list[i].classType, "enemy") == 0)
						continue;

					if(IS_SET(list[i].flags, ENT_FJEKYL) && list[i].inuse > 0)
					{
						if (strcmp(list[i].classType, "enemy") == 0)
						{
							REMOVE_FLAG(list[i].flags, ENT_SOLID);
						}
					}

					if(IS_SET(list[i].flags, ENT_FHYDE) && list[i].inuse > 0)
					{
						if (strcmp(list[i].classType, "enemy") == 0)
						{
							SET_FLAG(list[i].flags, ENT_SOLID);
						}
					}
				}
			}
	}
}
*/
/**********************************************************************************************//**
 * @fn	void CheckCollisions()
 *
 * @brief	Check collisions with one specific object.
 *
 * @author	iwh
 * @date	3/26/2015
 **************************************************************************************************/
/*void CheckCollisions()
{
	int i = 0;
	entity_t *e = listEntities;

	for (i = 0; i < MAX_ENTITIES; i++)
	{
	if (listEntities[i].inuse)
		{
			if (IS_SET(listEntities[i].flags, ENT_SOLID))
			{
				if (listEntities[i].xVel != 0 || listEntities[i].yVel != 0)
				{
					CheckCollision(&listEntities[i], &listEntities[i+1], MAX_ENTITIES-i);
					//ent is the current, target is next, how many people are left is last
					//you checked in one direction, don't check in the other
				}

			}
		}
	}
}
*/
/**********************************************************************************************//**
 * @fn	void CheckCollision (entity_t *ent, entity_t *targ, int max)
 *
 * @brief	Check collision with object from previous func.
 *
 * @author	iwh
 * @date	3/26/2015
 *
 * @param [in,out]	ent 	If non-null, the ent from prev. func.
 * @param [in,out]	targ	If non-null, the targ: entity next in memory.
 * @param	max				The maximum amount of entities that can be checked for collision.
 **************************************************************************************************/
/*void CheckCollision (entity_t *ent, entity_t *targ, int max)
{
	int i = 0;
	entity_t *e = listEntities;
		
	for (i = 0; i < max; i++)
	{
		if (isCollide (targ, ent))
		{	
			if (IS_SET(targ->flags, ENT_SOLID) && IS_SET(ent->flags, ENT_SOLID))
			{
				if (strcmp(targ->classType, "enemy") == 0 || strcmp(ent->classType, "enemy") == 0)
				{
					if (Game.levelState == HYDE_MODE && (IS_SET(targ->flags, ENT_FJEKYL) || IS_SET(ent->flags, ENT_FJEKYL)))
						continue;

					if (Game.levelState == JEKYLL_MODE && (IS_SET(targ->flags, ENT_FHYDE) || IS_SET(ent->flags, ENT_FHYDE)))
						continue;
						*/
					/* damage varys depending on enemy class 
					if (strcmp(targ->classname, "player") == 0)
					{
						//if (strcmp(ent->classname, "kid") == 0)
						//{
							//targ->currentHealth -= 0.5;
							//targ->currentAnger += 2;
						//}
						if (strcmp(ent->classname, "bomber") == 0)
						{
							targ->currentHealth -= 1;
							targ->currentAnger += 1;
						}
						if (strcmp(ent->classname, "bird") == 0)
						{
							targ->currentHealth -= 1;
							targ->currentAnger += 3;
						}
					}

					if (strcmp(ent->classname, "player") == 0)
					{
						if (strcmp(targ->classname, "kid") == 0)
						{
							ent->currentHealth -= 0.5;
							ent->currentAnger += 2;
						}
						if (strcmp(targ->classname, "bomber") == 0)
						{
							ent->currentHealth -= 1;
							ent->currentAnger += 1;
						}
						if (strcmp(targ->classname, "bird") == 0)
						{
							ent->currentHealth -= 1;
							ent->currentAnger += 3;
						}

					}
				}

				//ent->x -= ent->xVel;
				//ent->y -= ent->yVel;
			}
		}

		targ++;
	}
}
*/
/*
void collisions()
{
	int i, j;
	entity_t * list = listEntities;
	entity_t * collider1, * collider2;
	int max;

	for (i = 0; i < MAX_ENTITIES; i++)
	{
		if (list[i].inuse && IS_SET(list[i].flags, ENT_SOLID))
		{
			if (list[i].xVel != 0 || listEntities[i].yVel != 0)
			{
				collider1 = &list[i];
				collider2 = &list[i + 1];
				max = MAX_ENTITIES - i;

				for (j = 0; i < max; i++)
				{
					if (onCollision (targ, ent) && IS_SET(targ->flags, ENT_SOLID))
					{
						collisionEvents(targ, ent);
					}
				}

			}
		}
	}
}
*/

/**********************************************************************************************//**
 * @fn	void PlayerAlive ()
 *
 * @brief	Call basic player functions that make the player alive.  Simplifys code.
 *
 * @author	iwh
 * @date	4/10/2015
 **************************************************************************************************/
/*void PlayerAlive (entity_t * ent)
{

	if (ent != NULL && ent-> currentHealth && ent->currentHealth > 0)
	{
		move(ent);
		cameraSetOn(ent);
		show(ent);
	}
}
*/
/**********************************************************************************************//**
 * @fn	void move ( entity_t *ent )
 *
 * @brief	Moves the given entity (x, y) by adding or minusing the set velocity (xVel, yVel)
 * 			coordinates.  Also checks velocity for setting their animation state.
 *
 * @author	iwh
 * @date	3/26/2015
 *
 * @param [in,out]	ent	If non-null, the ent.
 **************************************************************************************************/
/*void move ( entity_t *ent ) //better name? also needs to be reorganized
{
	cpVect v;

	ent->x += ent->xVel;
	if (ent->xVel < 0)	
		setStateTo(getPlayer(), PL_LEFT); // anim states shouldn't be hard coded, different for every sprite!
	else if (ent->xVel == 0)
		setStateTo(getPlayer(), PL_IDLE);
	else
		setStateTo(getPlayer(), PL_RIGHT);

	if ( ( ent->x < 0 ) || ( ent->x + ent->width > L_WIDTH ) )
	{
		ent->x -= ent->xVel;
	}

	ent->y += ent->yVel;
	
	if ( ( ent->y < 0 ) || ( ent->y + ent->height > L_HEIGHT ) )
	{
		ent->y -= ent->yVel;
	}

	//ent->shape->surface_v = cpv(ent->x, 0.0);
	//ent->shape->u = 10/2;

	//v = cpBodyGetPos (ent->body);
	//ent->body->f = cpv(ent->xVel, ent->yVel);
	ent->x = v.x;
	ent->y = v.y;
	//cpBodyUpdateVelocity(ent->body, getSpace()->gravity, 0.00001, 0.00001);
}
*/
/*void show (entity_t *ent) //name change?
{
	if (ent)
	{
	// check states here, if state, animate function draws next frame
		if (Game.levelState == HYDE_MODE && ent->sprite->animationSet != NULL)
		{
			Animate(ent->sprite, &ent->sprite->animationSet->set[1], ent->x - getCamera().x, ent->y - getCamera().y);
			// if i don't get the address to the actual set from playerAnim, I will be editing the values of a temporary copy
			at some random spot in memory 
		}
		else
		{
			Animate(ent->sprite, &ent->sprite->animationSet->set[0], ent->x - getCamera().x, ent->y - getCamera().y);
		}
	}
	//if an eneny && they are a SILENT_IDLE and its spritesheet is loaded
	// animate the enemy, with this particular animation in the its animation set, at this position
}

void showEnt (entity_t *ent) //name change?
{
	surface(ent->sprite, getScreen(), ent->x - getCamera().x, ent->y - getCamera().y, NULL);
}

Check Collision - name change?
bool isCollide (entity_t *otherent, entity_t *ent)
{
	SDL_Rect A;
	SDL_Rect B;

	B.x = (Sint16)ent->x + ent->bBox.x;
	B.y = (Sint16)ent->y + ent->bBox.y;
	B.w = ent->bBox.w;
	B.h = ent->bBox.h;

	A.x = (Sint16)otherent->x + otherent->bBox.x;
	A.y = (Sint16)otherent->y + otherent->bBox.y;
	A.w = otherent->bBox.w;
	A.h = otherent->bBox.h;

	//SDL_FillRect(getScreen(), &A, SDL_MapRGB(getScreen()->format, 0x77, 0x77, 0x77));
	//SDL_FillRect(getScreen(), &B, SDL_MapRGB(getScreen()->format, 0x77, 0x77, 0x77));

	//combine bbox and players pos together check that in if statement
	if((A.x + A.w >= B.x) && (A.x <= B.x + B.w) && (A.y + A.h >= B.y) && (A.y <= B.y + B.h))
	{
		//printf("a\n");
		return true;
	}

	return false;
}

Thinking
void projThink (entity_t * self)
{	
	if (self->thinkflags == 10)
	{
		self->xVel = 0;
	}
	else if (self->thinkflags == 12)
	{
		freeEnt(self);
	}
	else
	{
		self->xVel -= 1;
	}

	self->thinkflags++;
	self->nextThink = getCurrentTime() + 300;
}

void alphaThink (entity_t *self)
{
	if (self->thinkflags == 10)
	{
		self->xVel = 0;
		//fire_Bomb(self);
	}
	else 
		self->xVel -= 0.2f; 
	if (self->x < 20)
		freeEnt(self);

	self->thinkflags++;
	self->nextThink = getCurrentTime() + 310;
}

void betaThink (entity_t *self)
{
	if (self->thinkflags == 7)
	{
		self->xVel = 0;
		//fire_Projectile(self);
	}
	else
	{
		self->xVel -= .20f;
	}

	if (self->x < 20)
		freeEnt(self);

	self->thinkflags++;
	self->nextThink = getCurrentTime() + 400;
}

void gammaThink (entity_t *self)
{
	float accel = 2;

	if (self->y > 100 && self->y < 500)
	{ self->yVel += -accel; }
	
	if (self->y > 500 || self->y < 100)
	{ self->yVel += accel; }

	//self->yVel += accel;

	self->thinkflags++;
	self->nextThink = getCurrentTime() + 600;
}

void kidSpawnThink (entity_t * self)
{
	spawnEntity("kid", self->x, self->y, "jekyll");
	//printf("cookie");
	self->nextThink = getCurrentTime() + 9000;
}

void bombSpawnThink (entity_t * self)
{
	spawnEntity("bomber", self->x, self->y, "hyde");
	self->nextThink = getCurrentTime() + 7500;
}

//Thinknum[0] - the boss's walk quadrant
void bossThink (entity_t *self)
{
	int accel = 1;

	int idleState = 1;

	switch (self->thinknums[0])
	{
		case 1:
			if (self->yVel == 0)
			{
				self->thinknums[0] = 2;
			}
			else
			{
				self->yVel++;
				self->xVel--;
			}
			break;
		case 2:
			if (self->xVel == 0)
			{
				self->thinknums[0] = 3;
				//fire_Projectile(self);
			}
			else
			{
				self->yVel++;
				self->xVel++;
			}
			break;
		case 3:
			if (self->yVel == 0)
			{
				self->thinknums[0] = 4;
			}
			else
			{
				self->yVel--;
				self->xVel++;
			}
			break;

		case 4:
			if (self->xVel == 0)
			{
				self->thinknums[0] = 1;
			}
			else
			{
				self->yVel--;
				self->xVel--;
			}
			break;

		default:
			self->yVel = -5;
			self->xVel = 0;
			self->thinknums[0] = 1;
			break;
	}

	self->nextThink = getCurrentTime() + 50;
}

void particleMove(entity_t * self)
{
	//printf("cookie");
	//entity_t * ent = initEnt();
	//sprintf(ent->classname, "particle");
	
	//ent->sprite = load ("graphic/particle/particle.png", 32, 32);

	//ent->show = showEnt;
	//SET_FLAG(ent->flags, ENT_SHOW);

	self->xVel = 5;
	self->yVel = 5;

	if (self->thinkflags == 10)
	{
		freeEnt(self);
	}

	self->thinkflags++;
	self->nextThink = getCurrentTime() + 5000;
}

void emitterThink (entity_t * self)
{
	spawnParticle(self->x, self->y, 12.0f);
	self->nextThink = getCurrentTime() + 500;
}

void initPlayer()
{
	entity_t * player = initEnt();

	//sprintf(player->classname, "player");

	player->x = 0;
	player->y = 340;

	player->width = 32;
	player->height = 32;
	
	//player->sprite = load("graphic/player/jekyll_sheet3.png", 32, 32);

	player->bBox.w = 32;
	player->bBox.h = 32;

	player->currentHealth = 100;
	player->max_health = 100;

	player->currentAnger = 1;
	player->maxAnger = 100;

	//player->sprite->animationSet = getAnimSet("sprite\\anim\\animsettest.json");

	SET_FLAG(player->flags, ENT_SOLID);
	SET_FLAG(player->flags, ENT_SHOW);

	//player->show = show;
	//player->think = PlayerAlive;
	*/
	/*
	player->body = cpBodyNew(10, cpMomentForCircle(10, 16, 0, cpvzero));
	player->shape = cpCircleShapeNew(player->body, 16, cpvzero);
	cpBodySetPos(player->body, cpv(player->x, player->y));
	cpShapeSetLayers(player->shape,CP_ALL_LAYERS);
	cpShapeSetCollisionType(player->shape, 2);
	cpShapeSetUserData(player->shape, (const cpDataPointer)player);
	*/
//}

/*void setStateTo(entity_t *ent, int animState)
{
	if (animState == ent->animState)
		return;
	else
		ent->animState = animState;
}

entity_t* getPlayer()
{
	int i;

	for (i = 0; i < MAX_ENTITIES; i++)
	{
		if (strcmp(listEntities[i].classname, "player") == 0)
		{
			return &listEntities[i];
		}
	}
	return NULL;
}*/

struct Entity* NewEntity()
{
	int i;

	for (i = 0; i < 255; i++)
	{
		if (_entityM[i].m_active == 0)
		{
			// clear that space, just in case there's anything left over from its last use
			memset(&_entityM[i], 0, sizeof(struct Entity));

			_entityM[i].m_active = 1;

			// any entity defaults? stay tooooooned

			_entity_max_recorded++;

			return &_entityM[i];
		}
	}

	return NULL;
}

void DeleteEntity(struct Entity *self)
{
	if (!self)
	{
		printf("WHA YOU DOIN\n"); // slog
		return;
	}

	self->m_active = 0;
	self->m_tags = 0;
	self->m_layer = 0;
	self->m_owner = NULL;
	
	memset(self->m_name, 0, sizeof(char) * 36);
}

void EntityMInit()
{
	int i;

	// if it's already been initialized/in memory, call return to exit this function
	// no need to do anything else
	if (_entityMInitialized)
		return;

	// get access to the new memory
	_entityM = (struct Entity *)malloc(sizeof(struct Entity)*255);
	
	// clear out the garbage that's in it
	memset(_entityM, 0, sizeof(struct Entity)*255);

	// format the memory to suit what it will be used for
	for (i = 0; i < 255; i++)
	{
		_entityM[i].m_active = 0;
		_entityM[i].m_tags = 0;
		_entityM[i].m_layer = 0;
		_entityM[i].m_owner = NULL;

		memset(_entityM[i].m_name, 0, sizeof(char) * 36);
	}

	// entity list now exists in memory
	_entityMInitialized = true;
}

void EntityMDel()
{
	int i;
	// for the highest number of possible entities
	for (i = 0; i < 255; i++)
	{
		// if it's alive/in use/active,
		if (_entityM[i].m_active)
		{
			// kill it
			DeleteEntity(&_entityM[i]);
		}
		// kill it all, just to make it sure i cleared that entity properly
		free(_entityM);
		//__entity_max = 0;

		// this is now false, since I am now clearing entityM from memory
		_entityMInitialized = false;
	}
}

int MaxRecordedEntities()
{
	return _entity_max_recorded;
}
