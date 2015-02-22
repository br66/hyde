//Include SDL to use... SDL
#include <SDL.h>
#include <SDL_image.h>

//Include header files I made
#include "boolean.h"
#include "graphics.h"
#include "gfunc.h"

SDL_Surface *screen = NULL; //application window
SDL_Surface *background = NULL; //image visible

SDL_Surface *sheet = NULL; //image for loading/showing
SDL_Rect clip[ 4 ]; //rectangle for breaking the image into sections

//For events (ex. key presses)
SDL_Event event;

//create main or else (error LNK2001: unresolved external symbol _SDL_main)
int main(int argc, char *argv[])
{	
	//boolean created for making sure the application stays active until this boolean equals true
	bool done = false;
	
	/* Start everything (SDL, open a window, etc.) and make sure it did it successfully */
	if ( init() == false)
	{
		return 1;
	}

	/* This func. loads all the sprites and checks that I did it correctly */
	if ( load_Files() == false)
	{
		return 1;
	}

	//top left position on the window
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = 100;
	clip[0].h = 100;

	//top right position on the window
	clip[1].x = 100;
	clip[1].y = 0;
	clip[1].w = 100;
	clip[1].h = 100;

	//botttom left position on the window
	clip[2].x = 0;
	clip[2].y = 100;
	clip[2].w = 100;
	clip[2].h = 100;

	//bottom right position on the window
	clip[3].x = 100;
	clip[3].y = 100;
	clip[3].w = 100;
	clip[3].h = 100;

	/* Fills the application window with the color white (0xFF, 0xFF, 0xFF) */
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

	//Instead of loading the image 4 times, we just show it four times.
	/* Presenting the background to the screen */
	//show_Surface( 0, 0, background, screen, NULL);
	//show_Surface( 0, 375, background, screen, NULL);
	//show_Surface( 500, 0, background, screen, NULL);
	//show_Surface( 500, 375, background, screen, NULL);

	/* Showing the spreadsheet now */
	show_Surface( 0, 0, sheet, screen, &clip[0]);
	show_Surface( 540, 0, sheet, screen, &clip[1]);
	show_Surface( 0, 380, sheet, screen, &clip[2]);
	show_Surface( 540, 380, sheet, screen, &clip[3]);

	/* Function so that the screen is constantly updated
	Think of a old motion picture; old picture gets replaced
	with new picture to show new things happening */
	SDL_Flip(screen);
	/* Another way to look at it would be frames: if this
	function is not used the game would basically run at 0
	frames per second.  You would see no movemnt or anything. */

	//The window will stay open for 2000/1000 sec a.k.a. 2 seconds.
	//SDL_Delay (2000);
	//SDL takes time in milliseconds.

	/* This is the gameloop, where things happen.  If you're coming from Unity,
	think of this as FixedUpdate, where things happen every time.  It runs continously
	waiting for user input, updating to show things happening, rendering, and tracking
	the passage of time.  It allows the game to continously run.  It is a basic state
	machine. I can't think of any other way to describe it; without it you have 
	no game. */
	
	/* GAME ------------------------------------------------------------------------- */
	do
	{
		//While there is still things to do
		while (SDL_PollEvent (&event))
		{
			//Do them
			//Unless, the user presses Quit (the x button on the window)

			if(event.type == SDL_QUIT)
			{
				//Game is done
				done = true;
			}
		}
	}
	
	while(!done); //Part of the do-while loop "Do game things while done is false (!done)"
	
	//When done equals true, the game escape the do-while loop (gameloop) and should reach the next line.
	//Free up the memory the game is using
	clear();

	//These last two lines fully exit the game.
	exit(0);
	return 0;

	/* GAME -------------------------------------------------------------------------- */
}