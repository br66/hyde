<<<<<<< HEAD
// .c
 
//#include <jansson.h> // find jansson or make own file parser, need to reinclude janssson.lib

// Standard C headers
#include <stdio.h>
#include <stdlib.h>

// Third-party library headers
#include <SDL.h>
#include <chipmunk.h>

// Custom headers
#include "boolean.h"

/*for time/delta time
extern Uint32 delta;
extern Uint32 start;


bool running = true;
//SDL_Color timeColor = { 255, 255, 255 }; // color of the clock, will remove clock, don't know how it works, make own?

// for keystates
static Uint8 *keystates;

//
for the mouse
extern int mouseX, mouseY;
extern int objX, objY;

// for level design
SDL_Event clickEvent;
extern sprite_t * testTile;
extern FILE * fp;
//

// for game states
extern game_t Game;

void mainmenuSetup()
{
	sprite_t * splash = NULL;
		
	splash = load("graphic/game/splash.png", 32, 32);
	splash->background = 1;

	setLvlState (NO_MODE);

	running = false;
}

void levelEdit()
{
	//Events();
	//SDL_Flip(getScreen());
}

void playCustomLevel()
{
	int i;

	if (running == true)
	{
		char msg[20];

		for( i = 0; i < 20; i++)
			msg[i] = 0;

		strcpy( msg, FormatTimeString(start));
		//setUpSeconds(msg, timeColor);
	}

	delta = SDL_GetTicks() - getCurrentTime();
	setCurrentTime();

	//cpSpaceStep(getSpace(), 0.1); // WHY I NO USE DELTA HERE
	//EntityAlive ();
	//CheckCollisions ();
	//Events ();

	keystates = (NULL);

	// checking keyboard input does not work outside of a function

	//SDL_Flip(getScreen());
}

void levelOne()
{
	int i;

		if (running == true)
		{
			char msg[20];

			for( i = 0; i < 20; i++)
				msg[i] = 0;

			strcpy( msg, FormatTimeString(start));
			//setUpSeconds(msg, timeColor);
		}
		
		delta = SDL_GetTicks() - getCurrentTime();
		printf("%i = %i - %i\n", delta, SDL_GetTicks(), getCurrentTime());
		setCurrentTime();

		//cpSpaceStep(getSpace(), 0.1);
		//EntityAlive ();
		//CheckCollisions ();
		Events ();

		keystates = (NULL);

		// checking keyboard input does not work outside of a function

		//SDL_Flip(getScreen());
}

void levelTwo()
{
	int i;

	if (running == true)
	{
		char msg[20];

		for( i = 0; i < 20; i++)
			msg[i] = 0;

		strcpy( msg, FormatTimeString(start));
		//setUpSeconds(msg, timeColor);
	}

	delta = SDL_GetTicks() - getCurrentTime();
	setCurrentTime();

	//cpSpaceStep(getSpace(), 0.1);
	//EntityAlive ();
	//CheckCollisions ();
	Events ();

	keystates = (NULL);

	// checking keyboard input does not work outside of a function

	//SDL_Flip(getScreen());
}*/
