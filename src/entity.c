/* The list of entites [listEntities] is made here.  Anytime that
the list needs to be used it will probably be done here from now on.  
If the need becomes too great, a get function will be made for it.

The player entity is made here; if needed in another file, use getPlayer().

InitEnt and FreeEnt have been edited/simplified.  The player's show function
now uses showFrame since the player's sprite is now a spritesheet.

getPlayer() and PlayerProperties is defined here at the bottom simplifying
code. */


#include "include.h"

static entity_t listEntities [MAX_ENTITIES];

entity_t *player = NULL; /* cannot be static, have to change its address, will implement playerProperties function to fix this */

/**********************************************************************************************//**
 * @fn	entity_t *Init_Ent (void)
 *
 * @brief	Initialises the ent.
 *
 * @return	null if it fails, else an entity_t*.
 **************************************************************************************************/

//Function has been simplified
entity_t *Init_Ent (void)
{
	int i;
	
	for (i = 0; i < MAX_ENTITIES; i++)
	{
		if (listEntities[i].inuse == 0)
		{
			listEntities[i].inuse = 1;
			return &listEntities[i];
		}
	}
	return NULL;

}

/**********************************************************************************************//**
 * @fn	void Free_Ent(entity_t *self)
 *
 * @brief	Frees ent from memory.
 *
 * @author	iwh
 * @date	3/26/2015
 *
 * @param [in,out]	self	If non-null, the self.
 **************************************************************************************************/

void Free_Ent(entity_t *self)
{
	self->inuse = 0;
	memset (self, 0, sizeof(*self));
}

/**********************************************************************************************//**
 * @fn	void EntityAlive()
 *
 * @brief	Calls all entities' think function in certain circumstances.
 *
 * @author	iwh
 * @date	3/26/2015
 **************************************************************************************************/

void EntityAlive() 
{
	int i = 0;
	entity_t *e = listEntities;
	for (i = 0; i < MAX_ENTITIES; i++)
	{
		if (listEntities[i].inuse && IS_SET(listEntities[i].flags, ENT_THINK) )
		{
			if (listEntities[i].nextThink <= getCurrentTime())
			{
				listEntities[i].think(&listEntities[i]);
			}
			if (e->xVel != 0)
			{
				e->x += e->xVel;
			}
			if (e->yVel != 0)
			{ e->y += e->yVel;}
		}
		e++;
	}
}

/**********************************************************************************************//**
 * @fn	void EntityShow ()
 *
 * @brief	Shows entitys' sprites onscreen.
 *
 * @author	iwh
 * @date	3/26/2015
 **************************************************************************************************/

void EntityShow ()
{
	int i = 0;
	entity_t *e = listEntities;
	for (i = 0; i < MAX_ENTITIES; i++)
	{
		if (listEntities[i].inuse)
		{
			if (IS_SET(listEntities[i].flags, ENT_SHOW))
			{
				if (listEntities[i].show != NULL)
				{
					(*listEntities[i].show)(&listEntities[i]);
				}
			}
		}
		e++;
	}
}

/**********************************************************************************************//**
 * @fn	void CheckCollisions()
 *
 * @brief	Check collisions with one specific object.
 *
 * @author	iwh
 * @date	3/26/2015
 **************************************************************************************************/

void CheckCollisions()
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
	//if entity exists, is solid and has a velocity...
}

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

void CheckCollision (entity_t *ent, entity_t *targ, int max)
{
	int i = 0;
	entity_t *e = listEntities;

	for (i = 0; i < max; i++)
	{
		if (isCollide (targ, ent)) //warning boss is solid in level 1
		{
			if IS_SET(targ->flags, ENT_SOLID){
			if (strcmp(targ->classname, "trigger") == 0)
			{	
				level = 2;

				player->x = 0;
				player->y = 340;
			}
			if (strcmp(targ->classname, "enemy") == 0) // if IS_SET targ ENT SOLID
				player->currentHealth -= 1; //health.w -= 1; 
			else
			{
				ent->x -= ent->xVel;
				ent->y -= ent->yVel;
			}}
		}
		targ++;
	}
}

void PlayerAlive ()
{
	move(player);
	set_Camera(player);
	show(player);
	//showFrame(getPlayer(), getScreen(), 200, getPlayer()->y - getCamera().y, 0);
}

/**********************************************************************************************//**
 * @fn	void handle_Input ( entity_t *ent )
 *
 * @brief	Handles the input described by player.
 *
 * @author	iwh
 * @date	3/26/2015
 *
 * @param [in,out]	ent	If non-null, the ent.
 **************************************************************************************************/

void handle_Input ( entity_t *ent )
{
	if (ent)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym )
			{
				case SDLK_UP: ent->yVel -= ent->height >> 4; break;
				case SDLK_DOWN: ent->yVel += ent->height >> 4; break;
				case SDLK_LEFT: ent->xVel -= ent->width >> 4; break;
				case SDLK_RIGHT: ent->xVel += ent->width >> 4; break;
			}
		}
		else if ( event.type == SDL_KEYUP )
		{
			switch ( event.key.keysym.sym)
			{
				case SDLK_UP: ent->yVel += ent->height >> 4; break;
				case SDLK_DOWN: ent->yVel -= ent->height >> 4; break;
				case SDLK_LEFT: ent->xVel += ent->width >> 4; break;
				case SDLK_RIGHT: ent->xVel -= ent->width >> 4; break;
			}
		}
	}
}

/**********************************************************************************************//**
 * @fn	void move ( entity_t *ent )
 *
 * @brief	Moves the given entity.
 *
 * @author	iwh
 * @date	3/26/2015
 *
 * @param [in,out]	ent	If non-null, the ent.
 **************************************************************************************************/

void move ( entity_t *ent )
{
	ent->x += ent->xVel;

	if ( ( ent->x < 0 ) || ( ent->x + ent->width > L_WIDTH ) )
	{
		ent->x -= ent->xVel;
	}

	ent->y += ent->yVel;
	
	if ( ( ent->y < 0 ) || ( ent->y + ent->height > L_HEIGHT ) )
	{
		ent->y -= ent->xVel;
	}
}

void show (entity_t *ent)
{
	//show_Surface (ent->x - getCamera().x, ent->y - getCamera().y, plyrSprite, getScreen(), NULL);
	showFrame(getPlayer(), getScreen(), getPlayer()->x - getCamera().x, getPlayer()->y - getCamera().y, 0);
}

void show_Ent (entity_t *ent)
{
	show_Surface (ent->x - getCamera().x, ent->y - getCamera().y, ent->sprite, getScreen(), NULL);
}

/* Check Collision */
bool isCollide (entity_t *otherent, entity_t *ent) /* example: A = Enemy, B = Player */
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

	//combine bbox and players pos together check that in if statement
	if((A.x + A.w >= B.x) && (A.x <= B.x + B.w) && (A.y + A.h >= B.y) && (A.y <= B.y + B.h))
		return true; 
		

	return false;
}

/* Thinking */
void projThink (entity_t *ent)
{	
	if (ent->thinkflags == 10)
	{
		ent->xVel = 0;
	}
	else if (ent->thinkflags == 12)
	{
		Free_Ent(ent);
	}
	else
	{
		ent->xVel -= 1;
	}
	ent->thinkflags++;
	ent->nextThink = getCurrentTime() + 300;
}

void alphaThink (entity_t *self)
{
	if (self->thinkflags == 10)
	{
		self->xVel = 0;
		fire_Bomb(self);
	}
	else 
		self->xVel -= 0.2f; 
		/* f stands for float */

	self->thinkflags++;
	self->nextThink = getCurrentTime() + 310;
}

void betaThink (entity_t *self)
{
	if (self->thinkflags == 7)
	{
		self->xVel = 0;
		fire_Projectile(self);
	}
	else
	{
		self->xVel -= .25;
	}

	self->thinkflags++;
	self->nextThink = getCurrentTime() + 400;
}

void gammaThink (entity_t *self)
{
	int accel = 2;

	if (self->y > 200 && self->y < 400)
	{ self->yVel += -accel; }
	
	if (self->y > 400 || self->y < 200)
	{ self->yVel += accel; }

	self->thinkflags++;
	self->nextThink = getCurrentTime() + 600;
}
//Thinknum[0] - the boss's walk quadrant
void bossThink (entity_t *self)
{
	int accel = 1;

	int idleState = 1;

	//printf("%d\n", self->thinknums[0]);

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
				fire_Projectile(self);
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

void playerProperties(entity_t *player)
{
	player->x = 0;
	player->y = 340;
	player->width = 32;
	player->height = 32;

	player->sprite = plyrSprite;

	player->bBox.w = 32;
	player->bBox.h = 32;

	player->currentHealth = 100;
	player->max_health = 100;

	player->framesperline = 10;

	SET_FLAG(player->flags, ENT_SOLID);
}

entity_t* getPlayer()
{
	return player;
}