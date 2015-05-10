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
	//json_t * start, * lvlname, * backgroundArray, * bgData, * lvlPieces, * entityObj, 
		/* classname, * flag, * x, * y;*/
	/*
	lvlname = json_string("name");
	backgroundArray = json_array();
	bgData = json_string("");
	lvlPieces = json_array();
	entityObj = json_object();
	classname = json_string("");
	flag = json_string("");
	x = json_integer(0);
	y = json_integer(0);
	*/
	//json_object_set_new(start, "", json_string(""));

	//draw the mouse
	if (SDL_GetMouseState(&mouseX, &mouseY))
	{
		//surface(testTile, getScreen(), (mouseX/32) * 32, (mouseY/32) * 32, NULL);
		//spawnEntity("platform 1", (mouseX/32) * 32, (mouseY/32) * 32, "jekyll");
		printf("spawn");
		//fputs("WTF", fp);  // WHAT THE FUUUUUUCK
		Events();
		SDL_Flip(getScreen());
		return;
	}

	Events();
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

	EntityAlive ();
	CheckCollisions ();
	Events ();

	keystates = SDL_GetKeyState (NULL);

	// checking keyboard input does not work outside of a function

	SDL_Flip(getScreen());
}

/* create main or else (error LNK2001: unresolved external symbol _SDL_main) 
int main(int argc, char *argv[])
{
	begin(); //initializes everything and main menu stuff

	// unusual printing glitch keeps replacing chars w/ "el/level1.json", fixing glitch here
	printf(" ");
	printf(" ");
	printf(" ");
	printf(" ");

	do
	{
		//update or Hyde()
		switch(Game.gameState)
		{
			case GSTATE_MENU:
				printf_s("menu state \n"); mainmenu(); break;
			case GSTATE_LEVELEDIT:
				printf("leveledit state \n"); leveledit(); break;
			case GSTATE_LEVEL1:
				printf("level 1 state \n"); levelOne(); break;
		}

		Events(); //will be changed to "events()" 
		SDL_Flip(getScreen());
	}
	while (!done);

	end();
	return 0;
}*/