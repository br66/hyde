#include "entity.h"
#include "graphics.h"
#include "weapon.h"

extern SDL_Event event;

extern SDL_Surface *screen;
extern SDL_Surface *dot;

extern SDL_Rect camera;

extern entity_t *wall;
extern entity_t *player;

extern Uint32 delta;

extern Uint32 currentTime;

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
		if (listEntities[i].inuse)
		{
			if (listEntities[i].nextThink <= currentTime && listEntities[i].think != NULL)
			{
				listEntities[i].think(&listEntities[i]);
			}
			if (e->xVel != 0)
			{
				e->bBox.x += (e->xVel * delta) >> 10;
			}
			if (e->yVel != 0)
			{ e->bBox.y += (e->yVel * delta) >> 10;}
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
			if (listEntities[i].show != NULL)
			{
				(*listEntities[i].show)(&listEntities[i]);
			}
		}
		e++;
	}
}

/* Entity in-game */
void init_Position (entity_t *ent)
{
	ent->x = 0;
	ent->y = 400;
	
	ent->xVel = 0;
	ent->yVel = 0;

	ent->width = 20;
	ent->height = 20;

	ent->bBox.x = ent->x;
	ent->bBox.y = ent->y;

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
				case SDLK_UP: ent->yVel -= ent->height / 2; break;
				case SDLK_DOWN: ent->yVel += ent->height / 2; break;
				case SDLK_LEFT: ent->xVel -= ent->width / 2; break;
				case SDLK_RIGHT: ent->xVel += ent->width / 2; break;
			}
		}
		else if ( event.type == SDL_KEYUP )
		{
			switch ( event.key.keysym.sym)
			{
				case SDLK_UP: ent->yVel += ent->height / 2; break;
				case SDLK_DOWN: ent->yVel -= ent->height / 2; break;
				case SDLK_LEFT: ent->xVel += ent->width / 2; break;
				case SDLK_RIGHT: ent->xVel -= ent->width / 2; break;
			}
		}
	}
}

void move ( entity_t *ent )
{
	ent->bBox.x += ent->xVel;

	if ( ( ent->bBox.x < 0 ) || ( ent->bBox.x + ent->width > L_WIDTH ) || (isCollide(ent->bBox, wall->bBox) ) )
	{
		ent->bBox.x -= ent->xVel;
	}

	ent->bBox.y += ent->yVel;
	
	if ( ( ent->bBox.y < 0 ) || ( ent->bBox.y + ent->height > L_HEIGHT ) || (isCollide(ent->bBox, wall->bBox)) )
	{
		ent->bBox.y -= ent->xVel;
	}
}

void show (entity_t *ent)
{
	show_Surface (ent->bBox.x - camera.x, ent->bBox.y - camera.y, dot, screen, NULL);
}

void show_Enemy (entity_t *ent)
{
	show_Surface (ent->bBox.x - camera.x, ent->bBox.y - camera.y, ent->sprite, screen, NULL);
}
 
void show_Relative (entity_t *ent)
{
	show_Surface(ent->bBox.x - camera.x, ent->bBox.y - camera.y, ent->sprite, screen, NULL);
	//printf("test");
}
void show_Background (entity_t *ent)
{
	//show_Surface (0, 0, background, screen, &camera);
}

/* Check Collision */
bool isCollide (SDL_Rect A, SDL_Rect B)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	//if (bottomA <= topB)
	//	return false;
	//if(topA >= bottomB)
	//	return false;
	//if (rightA <= leftB)
	//	return false;
	//if (leftA >= rightB)
	//	return false;

	//if (A.x <= B.x) && (B.x <= A.x + A.w) && (A.x <= B.y) && (B.y <= A.y + h)
	//{
	//	COLLIDE
	//}

	
	if (A.x >= B.x && A.x <= rightB && bottomA <= B.y)
		return true;
	if (A.x <= B.x && A.x <= rightB && bottomA <= B.y)
		return true;
	if (A.x <= rightB && bottomA <= B.y && A.y >= B.y)
		return true;
	if (A.x <= rightB && bottomA >= B.y && A.y >= B.y)
		return true;
	if (A.x <= rightB && bottomA <= B.y && A.y <= B.y)
		return true;
	
	// combine bbox and players pos together check that in if statement
	//if((box1.x + box1.w >= box2.x) && (box1.x <= box2.x+box2.w) && (box1.y + box1.h >= box2.y) && (box1.y <= box2.y+box2.h))
   // return true;

	return false;
}

/* Thinking */
void projThink (entity_t *ent)
{
	//ent->xVel -= 100;
	
	if (ent->thinkflags == 10)
	{
		ent->xVel = 0;
	}
	else
	{
		ent->xVel -= 100;
	//	ent->x -= 10;
	}
	ent->thinkflags++;
	ent->nextThink = currentTime + 300;
}

void alphaThink (entity_t *self)
{
	SDL_Rect b1, b2;

	b2.x = player->x + player->bBox.x;
	b2.y = player->y + player->bBox.y;
	b2.w = player->bBox.w;
	b2.h = player->bBox.h;

	b1.x = self->x + self->bBox.x;
	b1.y = self->y + self->bBox.y;
	b1.w = self->bBox.w;
	b1.h = self->bBox.h;

	if (self->thinkflags == 10)
	{
		self->xVel = 0;
		fire_Bomb(self);
	}
	else
		self->xVel -= 10;
/*
	if (isCollide (b1, b2))
	{
		self->xVel = 0;
		self->yVel = 0;
	}
*/
	self->thinkflags++;
	self->nextThink = currentTime + 300;
}

void betaThink (entity_t *self)
{
	if (self->thinkflags == 7)
	{
		self->xVel = 0;
		//printf("reacehd 20");
		fire_Projectile(self);
	}
	else
	{
		self->xVel -= 8;
	}

	self->thinkflags++;
	self->nextThink = currentTime + 400;
}

void gammaThink (entity_t *self)
{
	int accel = 10;

	if (self->bBox.y > 200 && self->bBox.y < 400)
	{self->yVel += -accel;}
	
	if (self->bBox.y > 400 || self->bBox.y < 200)
	{ self->yVel += accel; printf("wtf");}


	self->thinkflags++;
	self->nextThink = currentTime + 400;
}