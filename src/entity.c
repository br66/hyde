#include "include.h"

extern entity_t *wall;
extern entity_t *player;

/* Entity in memory */
entity_t *Init_Ent (void)
{
	int i;

	entity_t *ent;

	for (i = 0; i < max_ents+1; i++)
	{
		if(listEntities[i].inuse == 0) //if there is free memory in list
		{
			ent = &listEntities[i];
			ent->inuse = 1;
			max_ents++;
		}

		else if (max_ents < MAX_ENTITIES) //if there is memory at end of list
		{
			ent = &listEntities[max_ents++];
			ent->inuse = 1;
		}

		else if(i == max_ents) //if there is not enough slots for memory to be used
		{
			fprintf(stderr, "No Way! No Way! No Way! No Way?/n No Way! No Way! No Way! No Way?/n No Way! No Way! No Way! No Way?/n No Way! No Way! No Way! No Way?/n: %s\n", SDL_GetError());
			exit(1);
			return 0;
		}

		return ent;
	}
}

void Free_Ent(entity_t *self)
{
	self->inuse = 0;
}

void EntityAlive() 
{
	int i = 0;
	entity_t *e = listEntities;
	for (i = 0; i < MAX_ENTITIES; i++)
	{
		if (listEntities[i].inuse && IS_SET(listEntities[i].flags, ENTFLAG_THINK) )
		{
			if (listEntities[i].nextThink <= currentTime)
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

void EntityShow ()
{
	int i = 0;
	entity_t *e = listEntities;
	for (i = 0; i < MAX_ENTITIES; i++)
	{
		if (listEntities[i].inuse)
		{
			if (IS_SET(listEntities[i].flags, ENTFLAG_SHOW))
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
					//ent is the cur, target is next, how many people are left
					//you checked in one direction, don't check in the other
				}

			}
		}
	}
	//if entity exists, is solid and has a velocity...
}

void CheckCollision (entity_t *ent, entity_t *targ, int max)
{
	int i = 0;
	entity_t *e = listEntities;

	for (i = 0; i < max; i++)
	{
		if (isCollide (targ, ent))
		{
			ent->x -= ent->xVel;
			ent->y -= ent->yVel;
		}
		targ++;
	}
}

/* Entity in-game */
void init_Position (entity_t *ent)
{
	ent->x = 0;
	ent->y = 380;
	
	ent->xVel = 0;
	ent->yVel = 0;

	ent->width = 20;
	ent->height = 20;

	//ent->bBox.x = 20;
	//ent->bBox.y = 20;

	ent->bBox.w = 20;
	ent->bBox.h = 20;
}

void handle_Input ( entity_t *ent )
{
	if (ent)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym )
			{
				case SDLK_UP: ent->yVel -= ent->height >> 1; break;
				case SDLK_DOWN: ent->yVel += ent->height >> 1; break;
				case SDLK_LEFT: ent->xVel -= ent->width >> 1; break;
				case SDLK_RIGHT: ent->xVel += ent->width >> 1; break;
			}
		}
		else if ( event.type == SDL_KEYUP )
		{
			switch ( event.key.keysym.sym)
			{
				case SDLK_UP: ent->yVel += ent->height >> 1; break;
				case SDLK_DOWN: ent->yVel -= ent->height >> 1; break;
				case SDLK_LEFT: ent->xVel += ent->width >> 1; break;
				case SDLK_RIGHT: ent->xVel -= ent->width >> 1; break;
			}
		}
	}
}

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
	show_Surface (ent->x - camera.x, ent->y - camera.y, dot, screen, NULL);
}

void show_Enemy (entity_t *ent)
{
	show_Surface (ent->x - camera.x, ent->y - camera.y, ent->sprite, screen, NULL);
}
 
void show_Relative (entity_t *ent)
{
	show_Surface(ent->x - camera.x, ent->y - camera.y, ent->sprite, screen, NULL);
}

/* Check Collision */
bool isCollide (entity_t *otherent, entity_t *ent) /* example: A = Enemy, B = Player */
{
	SDL_Rect A;
	SDL_Rect B;

	B.x = ent->x + ent->bBox.x;
	B.y = ent->y + ent->bBox.y;
	B.w = ent->bBox.w;
	B.h = ent->bBox.h;

	A.x = otherent->x + otherent->bBox.x;
	A.y = otherent->y + otherent->bBox.y;
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
	else
	{
		ent->xVel -= 1;
	}
	ent->thinkflags++;
	ent->nextThink = currentTime + 300;
}

void alphaThink (entity_t *self)
{
	if (self->thinkflags == 10)
	{
		self->xVel = 0;
		fire_Bomb(self);
	}
	else
		self->xVel -= .2;

	self->thinkflags++;
	self->nextThink = currentTime + 310;
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
	self->nextThink = currentTime + 400;
}

void gammaThink (entity_t *self)
{
	int accel = 10;

	if (self->y > 200 && self->y < 400)
	{ self->yVel += -accel; }
	
	if (self->y > 400 || self->y < 200)
	{ self->yVel += accel; }

	self->thinkflags++;
	self->nextThink = currentTime + 400;
}
//Thinknum[0] - the boss's walk quadrant
void bossThink (entity_t *self)
{
	int accel = 1;

	int idleState = 1;
	//if y=0 , quad 2

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

	//self->thinkflags++;
	self->nextThink = currentTime + 50;
}

void wallThink (entity_t *self)
{
	//printf("0");

	//if (!isCollide(wall, player))
		//	printf("0");
		//else{
			//player->xVel = 0;
			//player->yVel = 0;
		//}

	self->nextThink = currentTime + 50;

	printf("%f || %f\n", player->x, player->y);
}