#include <SDL.h>

#include "boolean.h"
#include "gfunc.h"
#include "graphics.h"

//These SDL surfaces already exist in game.c
//I am grabbing them from that file because
//I need it here.
extern SDL_Surface *screen;
extern SDL_Surface *sheet;
extern SDL_Surface *background;

// Start everything
bool init()
{
	//Initialize SDL and checks if it did it successfully
	/*SDL's subsystems (video, audio, timers, engine components) are started up */
	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
	{
		return false;
	}

	//Set up the screen and check if it did it successfully
	/*Fourth argument creates the screens surface in system memory */
	screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, BITSPERPIXEL, SDL_SWSURFACE);
	if (screen == NULL)
	{
		return false;
	}

	/* Setting the window title */
	SDL_WM_SetCaption ("Game", NULL);

	/* If I didn't screw up anything, return true. */
	return true;
}

/* for loading the files all at once, foreshadow to precaching? */
bool load_Files()
{
	/*LOADING BACKGROUND */
	background = load_Image("sprite/tree.bmp");
	if (background == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	/* LOADING SPRITESHEET */
	sheet = load_Image("sprite/dots.png");
	if (sheet == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	return true;
}

/* for program exiting, cleaning and freeing up memory */
void clear()
{
	/* Freeing up memory by getting rid of these surfaces (images) */
	SDL_FreeSurface (sheet);
	SDL_FreeSurface (background);

	//Will free the screen surface and close SDL
	SDL_Quit();
}
