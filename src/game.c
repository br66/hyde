#include "include.h"
#include "game.h"
#include "spawn.h"

// for time/delta time
static Uint32 delta = 0;
static Uint32 start = 0;

// for keystates
static Uint8 *keystates;

// for game states
extern game_t Game;

//temp
extern SDL_Event event;

//for the main game loop
bool done = false;

void mainmenu()
{
	SDL_Surface * splash;
	SDL_Surface * optimizedSplash;

	splash = IMG_Load("graphic/game/splash.png");
	if (splash == NULL)
	{
		fprintf(stderr, "could not load splash image \n", SDL_GetError());
		exit(0);
	}
	optimizedSplash = SDL_DisplayFormat(splash);
	if (optimizedSplash == NULL)
	{
		fprintf(stderr, "could not load splash image \n", SDL_GetError());
		exit(0);
	}
	SDL_BlitSurface(optimizedSplash, NULL, getScreen(), NULL);
	SDL_FreeSurface(splash);
	SDL_FreeSurface(optimizedSplash);

	do
	{
		Events();
		SDL_Flip(getScreen());
	}
	while (Game.gameState == GSTATE_MENU);
}

void leveledit()
{
	SDL_Surface * levelEditScreen;
	SDL_Surface * optimizedEdit;

	levelEditScreen = IMG_Load("graphic/game/blackscreen.png");
	if (levelEditScreen == NULL)
	{
		fprintf(stderr, "could not load splash image \n", SDL_GetError());
		exit(0);
	}
	optimizedEdit = SDL_DisplayFormat(levelEditScreen);
	if (optimizedEdit == NULL)
	{
		fprintf(stderr, "could not load splash image \n", SDL_GetError());
		exit(0);
	}
	SDL_BlitSurface(optimizedEdit, NULL, getScreen(), NULL);
	SDL_FreeSurface(levelEditScreen);
	SDL_FreeSurface(optimizedEdit);

	do
	{
		Events();
		SDL_Flip(getScreen());
	}
	while (Game.gameState == GSTATE_LEVELEDIT);
}

void levelOne()
{
	// everything initialized at the beginning must be removed from memory at the end
	//init background: first background out of 2 for level 1
	sprite_t * bglvl1_1 = load("graphic/level/bg/newbglvl1_1.png", 32, 32); //test
	
	initPlayer();

	// load level one
	loadLevel ("level 1");

	setLvlState(JEKYLL_MODE);

	do
	{
		/* draw level one */
		surface(bglvl1_1, getScreen(),0,0,NULL);

		EntityAlive();
		entityShowSwitch ();
		CheckCollisions();
		Events ();

		keystates = SDL_GetKeyState (NULL);

		// checking keyboard input does not work outside of a function

		SDL_Flip(getScreen());
	}
	while(Game.gameState == GSTATE_LEVEL1);
	
	/* reset entities list */
	closeEntities();
	initEntities();

	/* de-init and reset sprite list*/
	closeSprites();
	initSprites();
}

/* create main or else (error LNK2001: unresolved external symbol _SDL_main) */
int main(int argc, char *argv[])
{
	begin(); //initializes everything and main menu stuff

	do
	{
		//update or Hyde()
		switch(Game.gameState)
		{
			case GSTATE_MENU:
				printf("menu state \n"); mainmenu(); break;
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
}