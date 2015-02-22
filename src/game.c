#include <SDL.h>
#include <SDL_image.h>

#include "boolean.h"
#include "graphics.h"

SDL_Surface *screen = NULL; //application window
SDL_Surface *message = NULL; //image for loading/showing
SDL_Surface *background = NULL; //image visible

//For events (ex. key presses)
SDL_Event event;

/* game functions ----------------------------------------------------------------------------------------------------------------------------- */

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
	/*LOADING IMAGE ONE */
	background = load_Image("sprite/tree.bmp");
	if (background == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	/*LOADING IMAGE TWO */
	message = load_Image("sprite/pass.bmp");
	if (message == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	return true;
}

/* for program exiting, cleaning and freeing up memory */
void clear()
{
	SDL_FreeSurface (message);
	SDL_FreeSurface (background);

	//Will free the screen surface and close SDL
	SDL_Quit();
}

/* ---------------------------------------------------------------------------------------------------------------------------------------------- */

//create main or else (error LNK2001: unresolved external symbol _SDL_main)
int main(int argc, char *argv[])
{	
	bool done = false;
	
	if ( init() == false)
	{
		return 1;
	}

	if ( load_Files() == false)
	{
		return 1;
	}

	/* Efficiency: Instead of loading the image 4 times,
	we just show it four times. */

	/* Presenting the background to the screen */
	show_Surface( 0, 0, background, screen);
	show_Surface( 0, 375, background, screen);
	show_Surface( 500, 0, background, screen);
	show_Surface( 500, 375, background, screen);

	/* Showing the pass image now */
	show_Surface( 0, 0, message, screen);

	/* Function so that the screen is constantly updated
	Think of a old motion picture; old picture gets replaced
	with new picture to show new things happening */
	/* Another way to look at it would be frames: if this
	function is not used the game would basically run at 0
	frames per second.  You would see no movemnt or anything. */
	SDL_Flip(screen);

	//The window will stay open for 2000/1000 sec a.k.a. 2 seconds.
	//SDL takes time in milliseconds.
	//SDL_Delay (2000);

	do
	{
		//while there is still things to do
		while (SDL_PollEvent (&event))
		{
			//do them

			if(event.type == SDL_QUIT)
			{
				done = true;
			}
		}
	}
	
	while(!done);
	clear();
	exit(0);
	return 0;
}