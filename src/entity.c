#include "entity.h"
#include "graphics.h"

extern SDL_Event event;

extern SDL_Surface *screen;
extern SDL_Surface *dot;

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
	}
	max_ents++;
	return ent;
}

void Free_Ent(entity_t *self)
{
	self->inuse = 0;
}

//---------------------------------------------------

void reset_Position (entity_t *ent)
{
	ent->x = 0;
	ent->y = 0;
	
	ent->xVel = 0;
	ent->yVel = 0;

	ent->width = 10;
	ent->height = 10;
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
	//printf("%i", ent->y);
	ent->x += ent->xVel;

	if ( ( ent->x < 0 ) || ( ent->x + ent->width > SCREEN_WIDTH ) )
	{
		//move back
		ent->x -= ent->xVel;
	}

	ent->y += ent->yVel;
	
	if ( ( ent->y < 0 ) || ( ent->y + ent->height > SCREEN_HEIGHT ) )
	{
		//move back
		ent->y -= ent->xVel;
	}
}

void show (entity_t *ent)
{
	show_Surface (ent->x, ent->y, dot, screen, NULL);
}