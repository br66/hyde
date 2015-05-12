#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include "include.h"
#include "spawn.h"
#include <chipmunk.h>

// for time/delta time
static Uint32 delta = 0;
Uint32 start = 0;
bool running = true;
SDL_Color timeColor = { 255, 255, 255 };

// for keystates
static Uint8 *keystates;

// for the mouse
extern int mouseX, mouseY;
extern int objX, objY;

// for level design
SDL_Event clickEvent;
extern sprite_t * testTile;
extern FILE * fp;

// for game states
extern game_t Game;

//temp
extern SDL_Event event;

//for the main game loop
bool done = false;

int main(int argc, char *argv[])
{
	bool done = false;

	begin(); //getting basic assets
	
	do
	{
		pull(); //input
		update();
		draw();
	}
	while (!done);
	
	return 0;
}

void pull()
{
	Events();
}

void update()
{
	SDL_Flip(getScreen());

	switch (Game.gameState)
	{
		case -1:
			end(); break;
		case GSTATE_LEVEL1:
			levelOne(); //updates level one
			break;
		case GSTATE_LEVEL2:
			levelTwo();
			break;
		case GSTATE_LEVELEDIT:
			levelEdit();
			break;
		case GSTATE_PLAYEDIT:
			playCustomLevel();
			break;
		case GSTATE_GAMEOVER:
			Events();
			break;
	}
}

void draw()
{
	showBackgrounds ();

	switch (Game.gameState)
	{
		case GSTATE_LEVEL1:
			entityShowSwitch ();
			updateHUD ();
			break;
		case GSTATE_LEVEL2:
			entityShowSwitch ();
			updateHUD ();
			break;
		case GSTATE_LEVELEDIT:
			entityShowSwitch ();
			break;
		case GSTATE_PLAYEDIT:
			entityShowAll();
			updateHUD();
			break;
		case GSTATE_GAMEOVER:
			break;
	}
}


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
	Events();
	SDL_Flip(getScreen());
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

	cpSpaceStep(getSpace(), 0.1);
	EntityAlive ();
	CheckCollisions ();
	Events ();

	keystates = SDL_GetKeyState (NULL);

	// checking keyboard input does not work outside of a function

	SDL_Flip(getScreen());
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
			setUpSeconds(msg, timeColor);
		}

		delta = SDL_GetTicks() - getCurrentTime();
		setCurrentTime();

		cpSpaceStep(getSpace(), 0.1);
		EntityAlive ();
		CheckCollisions ();
		Events ();

		keystates = SDL_GetKeyState (NULL);

		// checking keyboard input does not work outside of a function

		SDL_Flip(getScreen());
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
		setUpSeconds(msg, timeColor);
	}

	delta = SDL_GetTicks() - getCurrentTime();
	setCurrentTime();

	cpSpaceStep(getSpace(), 0.1);
	EntityAlive ();
	CheckCollisions ();
	Events ();

	keystates = SDL_GetKeyState (NULL);

	// checking keyboard input does not work outside of a function

	SDL_Flip(getScreen());
}

/**/