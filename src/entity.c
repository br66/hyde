#include "entity.h"
#include "graphics.h"
//#include "boolean.h"

extern SDL_Event event;

extern SDL_Surface *screen;
extern SDL_Surface *dot;

extern SDL_Rect camera;

extern entity_t *wall;

//Entity init now fully functional, up to 3 entities tested
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
		}

		return ent;
	}
}

void Free_Ent(entity_t *self)
{
	self->inuse = 0;
}

//---------------------------------------------------

void reset_Position (entity_t *ent)
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
	//printf("yes");
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
	//printf("%i", ent->bBox.x);
	ent->bBox.x += ent->xVel;

	if ( ( ent->bBox.x < 0 ) || ( ent->bBox.x + ent->width > L_WIDTH ) || (check_Col(ent->bBox, wall->bBox) ) )
	{
		//move back
		ent->bBox.x -= ent->xVel;
	}

	//printf("%i", ent->bBox.y);
	ent->bBox.y += ent->yVel;
	
	if ( ( ent->bBox.y < 0 ) || ( ent->bBox.y + ent->height > L_HEIGHT ) || (check_Col(ent->bBox, wall->bBox)) )
	{
		//move back
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

/* Check Collision */
bool check_Col (SDL_Rect A, SDL_Rect B)
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