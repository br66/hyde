#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"

//create main or else (error LNK2001: unresolved external symbol _SDL_main)
int main(int argc, char *argv[])
{
	SDL_Surface *message = NULL; //image for loading/showing
	//SDL_Surface *background = NULL; //image visible
	SDL_Surface *screen = NULL;

	/*SDL'S subsystems (video, audio, timers, engine components) are started up */
	SDL_Init(SDL_INIT_EVERYTHING);
	
	/*Fourth argument creates the screens surface in system memory */
	screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, BITSPERPIXEL, SDL_SWSURFACE);

	/* Setting the window title */
	SDL_WM_SetCaption ("Game", NULL);
	
	/*LOADING IMAGE ONE */
	message = load_Image("pass.bmp");
	if (message == NULL)
	{
		printf("error: %s\n", SDL_GetError());
	}

	show_Surface( 0, 0, message, screen);

	SDL_Flip(screen);
	SDL_Delay (2000);

	SDL_FreeSurface (message);

	SDL_Quit();

	//int done;

	//done = 0;
	//////////////////////////
	//do
	//{

	//}
	//////////////////////////
	//while(!done);
	//exit(0);
	return 0;
}