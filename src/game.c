//Include SDL to use... SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//Include header files I made
#include "boolean.h"
#include "graphics.h"
#include "gfunc.h"

/* These SDL instances already exist in gfunc.c. I am 
grabbing them from there because I need it here. */
extern SDL_Surface *screen;
extern SDL_Surface *background;

extern SDL_Surface *upMessage;
extern SDL_Surface *downMessage;
extern SDL_Surface *leftMessage;
extern SDL_Surface *rightMessage;

extern SDL_Surface *message;

extern TTF_Font *font;
extern SDL_Color textColor;
extern SDL_Rect clips[4];

extern SDL_Event event;

Uint8 *keystates;



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
	
	//Telling the game what the messages will say, what color, and what font to use
	upMessage = TTF_RenderText_Solid(font, "Up", textColor);
	if ( upMessage == NULL)
	{
		return 1;
	}

	downMessage = TTF_RenderText_Solid(font, "Down", textColor);
	if ( upMessage == NULL)
	{
		return 1;
	}

	leftMessage = TTF_RenderText_Solid(font, "Left", textColor);
	if ( upMessage == NULL)
	{
		return 1;
	}

	rightMessage = TTF_RenderText_Solid(font, "Right", textColor);
	if ( upMessage == NULL)
	{
		return 1;
	}

	/* Fills the application window with the color white (0xFF, 0xFF, 0xFF) */
	//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

	//Instead of loading the image 4 times, we just show it four times.
	/* Presenting the background to the screen */
	show_Surface( 0, 0, background, screen, NULL);
	show_Surface( 0, 375, background, screen, NULL);
	show_Surface( 500, 0, background, screen, NULL);
	show_Surface( 500, 375, background, screen, NULL);

	//show_Surface(10, 10, upMessage, screen, NULL);

	/* Showing the spreadsheet now */
	//show_Surface( 0, 0, sheet, screen, &clip[0]);
	//show_Surface( 540, 0, sheet, screen, &clip[1]);
	//show_Surface( 0, 380, sheet, screen, &clip[2]);
	//show_Surface( 540, 380, sheet, screen, &clip[3]);

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
			/*In the event that a key has been pressed...
			if ( event.type == SDL_KEYDOWN )
			{
				//system for checking what key has been pressed
				switch ( event.key.keysym.sym )
				{
					case SDLK_UP: message = upMessage; break;
					case SDLK_DOWN: message = downMessage; break;
					case SDLK_LEFT: message = leftMessage; break;
					case SDLK_RIGHT: message = rightMessage; break;
				}
			}*/


			//If the user presses Quit (the x button on the window)
			if(event.type == SDL_QUIT)
			{
				//Game is done
				done = true;
			}
		}
		keystates = SDL_GetKeyState( NULL );
		/* Showing the text only when a message needs to be displayed */
		//if (message != NULL)
		//{

			/* Text keeps overlapping each other, recreate bg to fix problem */
			show_Surface (0, 0, background, screen, NULL);

			/* Show message in the middle of the screen" */
			//show_Surface( (SCREEN_WIDTH - message->w) / 2, (SCREEN_HEIGHT - message->h)/2, message, screen, NULL );
			/* Resets message */
			//message = NULL;
		//}

		

		//When up is pressed
		if ( keystates[SDLK_UP] )
		{
			show_Surface ( (SCREEN_WIDTH - upMessage->w ) / 2, ( SCREEN_HEIGHT / 2 - upMessage->h ) / 2, upMessage, screen, NULL );
		}
		//when down is pressed
		if (keystates [SDLK_DOWN] )
		{
			show_Surface ( (SCREEN_WIDTH - downMessage->w ) / 2, (SCREEN_HEIGHT / 2 - downMessage->h ) / 2 + (SCREEN_HEIGHT / 2), downMessage, screen, NULL);
		}
		if (keystates [SDLK_LEFT] )
		{
			show_Surface ( (SCREEN_WIDTH /2 - leftMessage->w ) / 2, (SCREEN_HEIGHT - leftMessage->h ) / 2, leftMessage, screen, NULL);
		}
		if (keystates [SDLK_RIGHT] )
		{
			show_Surface ( (SCREEN_WIDTH /2 - rightMessage->w ) / 2 + (SCREEN_WIDTH / 2), (SCREEN_HEIGHT - rightMessage->h) / 2, rightMessage, screen, NULL);
		}

		/* Function so that the screen is constantly updated so you can see things happening as they happen */
		SDL_Flip(screen);
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