/* companion to game.c file */

//#include <jansson.h>
#include <stdio.h>
#include "include.h"
#include "spawn.h"

game_t Game;

bool left = false;
bool right = false;

// for external controls
SDL_Joystick * joystick;
SDL_JoyButtonEvent joyEvent;

// for time
static SDL_Surface *seconds = NULL;
static Uint32 currentTime = 0;
static TTF_Font *time = NULL;  // to rename time font 
bool done;
extern Uint32 start;
extern bool running;
static bool pause = false;
//long pauseTime;

// for the mouse
static sprite_t * mouseSprite;
int mouseX, mouseY;
int objX = 0;
int	objY = 0;

//for lvldesign
FILE *fp;
sprite_t * testTile = NULL; // to be replaced with list of defined level objects?
extern entity_t listEntities [MAX_ENTITIES];
static int spawned;

// the camera
static SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

// for events
SDL_Event event;

// for the hud
SDL_Rect health;
SDL_Rect anger;

// for physics
cpSpace * space;

// for music
Mix_Music * bgMusic;

extern "C" 
{ 
	FILE __iob_func[3] = { *stdin,*stdout,*stderr }; 

	extern int	vfprintf(FILE *, const char *, va_list);
}



// for beginning of game
void begin()
{
	// project2017: remove SDL1 and change to SDL2

	/*
	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
		printf("SDL 1.2 error \n", SDL_GetError());
	else printf("sdl init success \n");

	if (Mix_OpenAudio ( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
		printf("SDL Mixer error \n", SDL_GetError());
	else printf("sdl mixer success \n");

	if ( TTF_Init() == -1 )
		printf("SDL TTF error \n", SDL_GetError());
	else printf("sdl ttf success \n");

	// graphics/sprites
	initSprites();
	if (setupScreen() == false)
		printf("problem setting up screen \n", SDL_GetError());
	else printf("screen is set up \n");

	// entities
	initEntities();

	time = TTF_OpenFont("font/lazy.ttf", 20);
	if ( time == NULL)
	{
		fprintf(stderr, "ttf font error: %s \n", SDL_GetError());
		return;
	}

	// joysticks controls tested w/ xbox 360 controller
	if (SDL_NumJoysticks() > 0)
	{
		joystick = SDL_JoystickOpen(0);

		if (joystick)
		{
			printf("Joystick successfully opened -- Name: %s\n", SDL_JoystickName(0));
			printf("# of Axes: %d\n", SDL_JoystickNumAxes(joystick));
			printf("# of Buttons: %d\n", SDL_JoystickNumButtons(joystick));
			printf("# of hats: %d\n", SDL_JoystickNumHats(joystick));
		}
		else
		{
			printf("could not find joystick");
		}
	}

	bgMusic = Mix_LoadMUS("sound/Bloody Tears_ Super Castlevania 4 Music.wav");

	if (Mix_PlayMusic (bgMusic, -1) == -1)
		return;
	*/
	//start the game at the menu
	//setGameState(GSTATE_MENU, true);
	//setLvlState(NO_MODE);
	//SDL_WM_SetCaption ("HYDE", NULL);
}

// for end of game
void end()
{
	/*if (SDL_JoystickOpened(0))
		SDL_JoystickClose(joystick);
	
	Mix_HaltMusic();

	Mix_CloseAudio();
	TTF_Quit();
	closeScreen();
	closeSprites();
	closeEntities();
	SDL_Quit();*/
	exit(0);
}

void setGameState(int gameState, bool setup)
{
	int lvlObject;

	const char * classname, * flag;
	int x, y;

	if (setup == true)
	{
			// if open, last state was level edit, save all entities from mode in file
			if (fp != NULL)
			{
				fprintf (fp, "{\n\t\"name\" : \"level edit\",\n\t\"background\" : [\"bglvl1_1.png\", \"bglvl_1.png\"],\n\n\t \"level\" : \n\t[\n");
				for (lvlObject = 0; lvlObject < spawned; lvlObject++)
				{
					classname = listEntities[lvlObject].classname;
					flag = listEntities[lvlObject].mode;
					x = listEntities[lvlObject].x;
					y = listEntities[lvlObject].y;

					fprintf(fp , "\t\t{\n\t\t\t\"classname\" : \"%s\",\n\t\t\t\"flag\" : \"%s\",\n\t\t\t\"x\" : %i,\n\t\t\t\"y\" : %i\n\t\t}", classname, flag, x, y);
					//printf("\t{\n\"classname\" : \"%s\",\n\"flag\" : \"%s\",\n\"x\" : %i,\n\"y\" : %i\n}", classname, flag, x, y);

					if (lvlObject < spawned - 1)
					{
						fprintf(fp, ",\n\n");
					}
				}

				fprintf(fp, "\n\t]\n}");
				
				fclose(fp);
				spawned = 0;
			}

			if (space != NULL)
			{
				cpSpaceFree(space);
				space = NULL;
				printf("space has been freed\n");
			}

			//closeSprites();
			//closeEntities();

		switch (gameState) //local gameState
		{
			case GSTATE_MENU:
				mainmenuSetup(); break;
			case GSTATE_LEVEL1:
				initSprites();
				initEntities();
				levelOneSetup(); break;
			case GSTATE_LEVEL2:
				initSprites();
				initEntities();
				levelTwoSetup(); 
				break;
			case GSTATE_GAMEOVER:
				gameOverSetup(); 
				break;
			case GSTATE_LEVELEDIT:
				initSprites();
				initEntities();
				levelEditSetup();
				break;
			case GSTATE_PLAYEDIT:
				initSprites();
				initEntities();
				customLevelSetup();
				break;
		}
	}

	if (Game.gameState == gameState)
		return;
	else
		Game.gameState = gameState;
}

// for setting the game state
void setLvlState (int levelState)
{
	if (Game.levelState == levelState)
		return;
	else
		Game.levelState = levelState;
}

/*
void loadLevel(char * level)
{
	int i, j;

	json_t * parser;
	json_error_t error; // error handler

	json_t *data, *name, *background, *lvlpieces, *entity;
	json_t *classname, *flag, *x, *y;

	space = cpSpaceNew();
	cpSpaceSetGravity(space, cpv(0, 0.9));

	// can't case switch strings :/
	if (strcmp(level, "level 1") == 0)
	{
		printf("loading level one\n");
		parser = json_load_file("data/level/level1.json", 0, &error);
	}
	
	if (!strcmp(level, "level 2"))
	{
		printf("loading level two");
		parser = json_load_file("data/level/level2.json", 0, &error);
	}

	if (!strcmp(level, "custom level"))
	{
		printf("loading custom level");
		parser = json_load_file("data/level/lvlEdit.json", 0, &error);
	}

	if (strcmp(level, "boss 1") == 0)
	{
		printf("loading boss 1");
		//strcpy(level, level);
		return;
	}

	// loading the file

	if (!parser)
	{
		fprintf(stderr, "wtf no parser\n file may not exist\n or be good format");
		return;
	}
	if (!json_is_object(parser))
	{
		fprintf(stderr, "didn't find an object\n");
		json_decref(parser);
		return;
	}

	// name of level
	name = json_object_get(parser, "name");
	if(!json_is_string(name))
	{
		fprintf(stderr, "next line should've been the beginning of the lvl object");
		json_decref(parser);
		return;
	}
	printf("%s \n", json_string_value(name));

	// backgrounds for level
	background = json_object_get(parser, "background");
	if (!json_is_array(background))
	{
		fprintf(stderr, "didn't find an array\n");
		json_decref(parser);
		return;
	}
	for (i = 0; i < json_array_size(background); i++)
	{
		data = json_array_get(background, i);
		if (!json_is_string(data))
		{
			fprintf(stderr, "next line should've been an object");
			json_decref(parser);
			return;
		}
		//printf("%s \n", json_string_value(data));
	}
	
	// entities for level //if player already exists, get that address
	lvlpieces = json_object_get(parser, "level");
	if (!json_is_array(lvlpieces))
	{
		fprintf(stderr, "i was looking for the array of entities");
		json_decref(parser);
		return;
	}
	for (j = 0; j < json_array_size(lvlpieces); j++)
	{
		// get the entity
		entity = json_array_get(lvlpieces, j);
		if(!json_is_object(entity))
		{
			fprintf(stderr, "i was looking for the entity");
			json_decref(parser);
			return;
		}

		// get entity's attributes
		classname = json_object_get(entity, "classname");
		if (!json_is_string(classname))
		{
			fprintf(stderr, "no classname");
			json_decref(parser);
			return;
		}
		printf("%s\n", json_string_value(classname));

		flag = json_object_get(entity, "flag");
		if (!json_is_string(flag))
		{
			fprintf(stderr, "no flag");
			json_decref(parser);
			return;
		}
		//printf("%s\n", json_string_value(flag));

		x = json_object_get(entity, "x");
		if (!json_is_integer(x))
		{
			fprintf(stderr, "no x");
			json_decref(parser);
			return;
		}
		//printf("%d\n", json_integer_value(x));

		y = json_object_get(entity, "y");
		if (!json_is_integer(y))
		{
			fprintf(stderr, "no y");
			json_decref(parser);
			return;
		}
		//printf("%d\n", json_integer_value(y));

		spawnEntity(json_string_value(classname), (float)json_integer_value(x), (float)json_integer_value(y), json_string_value(flag));
	}
	
	json_decref(parser);
	printf("file data succesfully loaded\n");

	level = NULL; // failed attempt at glitch fix
	

	return;
}*/

/* gets, sets, and closers to reduce amount of externs */
SDL_Rect getCamera (void)
{
	return camera;
}

void cameraSetOn (entity_t *ent)
{
	int xmargin;
	xmargin = 1000;

	camera.x = ( ent->x + ent->width + xmargin / 2) - L_WIDTH / 8;
	camera.y = ( ent->y + ent->height / 1) - L_HEIGHT / 3;

	if ( camera.x < 0 )
		camera.x = 0;
	if ( camera.y < 0 )
		camera.y = 0;
	if ( camera.x > L_WIDTH - camera.w)
		camera.x = L_WIDTH - camera.w;
	if ( camera.y > L_HEIGHT - camera.h )
		camera.y = L_HEIGHT - camera.h;
}

SDL_Rect *addrCamera(void)
{
	return &camera;
}

TTF_Font *getFont (void)
{
	return time;
}

Uint32 getCurrentTime(void)
{
	return currentTime;
}
void setCurrentTime(void)
{
	currentTime = SDL_GetTicks();
}

/*
void getTime()
{
	if (pause)
		return pauseTime;
	else
		return SDL_GetTicks();
}
*/

SDL_Surface *getSeconds(void)
{
	return seconds;
}

void setUpSeconds(char* msg, SDL_Color textColor) //where to render to and what color
{
	seconds = TTF_RenderText_Solid (getFont(), msg, textColor);
	show_Surface ((SCREEN_WIDTH - (float)seconds->w ) * 1, 10, seconds, getScreen(), NULL); // BUT I DON'T WANNA DIVIIIIIIIIIIIIIIIDE

	SDL_FreeSurface( seconds );
}
void closeSeconds(void)
{
	if (!seconds)
	{
		SDL_FreeSurface (seconds);
	}
}

SDL_Event getEvents()
{
	return event;
}

void initHUD ()
{
	health.x = 10;
	health.y = 10;
	health.w = (getPlayer()->currentHealth * 100) / getPlayer()->max_health; //how do I get rid of division? can I?
	health.h = 10;

	anger.x = 115;
	anger.y = 10;
	anger.w = (getPlayer()->currentAnger * 100) / getPlayer()->maxAnger;
	anger.h = 10;
}

// for the player and hud
void updateHUD ()
{
	printf("%i", left);
	printf("%i", right);

	if (left && right)
		printf("both buttons are being pressed\n");

	health.w = (getPlayer()->currentHealth * 100) / getPlayer()->max_health; //how do I get rid of division? can I

	if (getPlayer()->currentHealth < 0)
	{
		getPlayer()->currentHealth = 0;
		setGameState(GSTATE_GAMEOVER, true);
		//printf("game over");
	}

	anger.w = (getPlayer()->currentAnger * 100) / getPlayer()->maxAnger; //how do I get rid of division? can I

	if (getPlayer()->currentAnger >= 100)
	{
		//printf("afadf");

		setLvlState(HYDE_MODE);
	}

	if (Game.levelState == HYDE_MODE)
		getPlayer()->currentAnger -= 0.05;

	if (Game.levelState == HYDE_MODE && getPlayer()->currentAnger < 0)
		{
			setLvlState(JEKYLL_MODE);
			getPlayer()->currentAnger = 0;
		}

	if (getPlayer()->currentHealth > 0)
		{
			SDL_FillRect ( getScreen(), &health, SDL_MapRGB ( getScreen()->format, 0, 0xFF, 0 ) );
			SDL_FillRect ( getScreen(), &anger, SDL_MapRGB ( getScreen()->format, 0x77, 0x77, 0x77 ) );
		}
}

SDL_Rect getHealthbar ()
{
	return health;
}

SDL_Rect getAngerBar ()
{
	return anger;
}

// for game events (ex. keyboard input)
// reminder: put player in level file
void Events()
{
	int x, y;

	if (Game.gameState != -1)
	{
		while (SDL_PollEvent (&event))
		{
			if (Game.gameState == GSTATE_LEVELEDIT)
			{
				switch (event.type)
				{
					case SDL_MOUSEBUTTONDOWN:
						{
							if (fp != NULL && SDL_GetMouseState(&mouseX, &mouseY))
							{
								// PUT ENTITY HERE, at end find all entities in world put in .json
								x = (mouseX/32) * 32;
								y = (mouseY/32) * 32;

								spawned++;
								printf("%i", spawned);
								
								spawnEntity ("platform 1", x, y, "jekyll");
							}
						}
				}
			}

			if(joystick && getPlayer() != NULL)
			{
				switch (event.type)
				{
					case SDL_JOYAXISMOTION:
						{
							if ( (event.jaxis.value < 0) || (event.jaxis.value > 3200))
							{
								switch (event.jaxis.axis)
								{
									case 0: 
										printf("up down\n"); 
										break;

									case 1:
									{
										if(getPlayer() != NULL)
										{
											getPlayer()->xVel = event.jaxis.value >> 14;
											printf("%f\n",getPlayer()->xVel);
											break;
										}
						
									}
								}

							}
							else
								getPlayer()->xVel = 0;
						}
					case SDL_JOYBUTTONDOWN:
					{
						switch (event.jbutton.button)
						{
							case 0: printf("the a button"); break;
							case 1: printf("the b button"); break;
							case 2: printf("the x button"); getPlayer()->yVel -= getPlayer()->height >> 5; break;
							case 3: printf("the y button"); break;
						}
						break;
					}
					case SDL_JOYBUTTONUP:
					{
						switch (event.jbutton.button)
						{
							case 0: printf("the a button"); break;
							case 1: printf("the b button"); break;
							case 2: printf("the x button up"); getPlayer()->yVel += getPlayer()->height >> 5; break;
							case 3: printf("the y button"); break;
						}
						break;
					}
				
				}
			}

			if ( event.type == SDL_KEYDOWN )
			{
				switch ( event.key.keysym.sym )
				{
					case SDLK_m:
						setGameState(GSTATE_MENU, true);
						break;
					case SDLK_l:
						setGameState(GSTATE_LEVELEDIT, true); printf("got here\n");
						break;
					case SDLK_1:
						setGameState(GSTATE_LEVEL1, true); printf("got here too\n");
						break;
					case SDLK_2:
						setGameState(GSTATE_LEVEL2, true);
						break;
					case SDLK_3:
						setGameState(GSTATE_PLAYEDIT, true);
						break;
					case SDLK_UP:
						{
							if(getPlayer() != NULL)
								getPlayer()->yVel -= getPlayer()->height >> 5; 
							break;
						}
					case SDLK_DOWN:
						{
							if(getPlayer() != NULL)
								getPlayer()->yVel += getPlayer()->height >> 5;
							break;
						}
					case SDLK_LEFT:
						{
							left = true;
							if(getPlayer() != NULL)
							{
								getPlayer()->xVel -= getPlayer()->width >> 5;
							}
							break;
						}
					case SDLK_RIGHT: 
						{
							right = true;
							if(getPlayer() != NULL)
							{
								getPlayer()->xVel += getPlayer()->width >> 5; 
							
							}
							break;
						}
				}

			}
			else if (event.type == SDL_KEYUP)
			{
				printf("no keys");
				switch ( event.key.keysym.sym )
				{
					case SDLK_UP:
						{
							if(getPlayer() != NULL)
								getPlayer()->yVel += getPlayer()->height >> 5; 
							break;
						}
					case SDLK_DOWN:
						{
							if(getPlayer() != NULL)
								getPlayer()->yVel -= getPlayer()->height >> 5; 
							break;
						}
					case SDLK_LEFT:
						{
							left = false;
							if(getPlayer() != NULL)
								getPlayer()->xVel += getPlayer()->width >> 5;
							break;
						}
					case SDLK_RIGHT:
						{
							right = false;
							if(getPlayer() != NULL)
								getPlayer()->xVel -= getPlayer()->width >> 5; 
							break;
						}
				}
			}

			if (event.type == SDL_QUIT)
			{
				done = true; // to call functions to prepare to close game
				setGameState(-1, false); // don't know if this is safe..
			}
		}
	}

	//if (joystick && Game.gameState != -1)
	//{
		//while (SDL_Polle
	//}
}

/* for time */
char *FormatNumber(Uint32 number, int min)
{
	/* Rough translation of timecode, will attempt to better clarify later */

	Uint32 value = number;  //The number we get from the raw time (which is in Uint32 form)
	static char array[10][20];  //Array w/ 3 10 rows & 20 columns
	static int buffer = 0; //creating a buffer, saving the numbers
	int count, x; // for counting

	buffer = (buffer + 1) % 10; //moves to the next spot in array? makes sure it doesn't go outside of 0-9?

	/* Unsigned integers should not be converted into char,
	therefore, we will count.  Everytime we get a number, we
	will increment the count */

	/* Everytime we count, we take the raw time and divide it by 10
	which gets rid of the number at the end. */

	for (count = 0; value != 0; count++)
		value /= 10;
	if(count < min) //???
		count = min;
	for (x = count; x > 0; x--) // The number of our count is equal to the number of integers that make up the raw time. 
	{
		/* Array length - 1 = entry in array. We will take the last number in uint32 ticks,
		 add it to the buffer and modulate it */
		array[buffer][x-1] = '0' + number % 10;
		// move on to the next number in uint32 ticks, keep doing this until x <= 0;
		number /= 10; 
	}
	if(count == 0){
		//if there is no number to count, then there is nothing there, therefore 0
		array[buffer][count] = '0';
		count++;
	}
	array[buffer][count] = '\0'; //use length of array to find end of array, make it \0, will signify end of array
	return array[buffer]; //???
}

char* FormatTimeString(Uint32 offset) //creates result var, converts raw time into h/m/s time and retruns it
{
	static char result[80]; /* doesn't change outside function */
	int i; // for counting
	char *hundreths, *seconds, *minutes, *hours;
	Uint32 ticks = SDL_GetTicks() - offset; /* we dont start the time automatically, we wait a few milsecs to have something to compare the time to */
	Uint32 num = ticks; // raw time
	for(i = 0;i <= TIMEUNIT_HOURS;i++){
		switch(i){
		case TIMEUNIT_HUNDRETHS:
			hundreths = FormatNumber((ticks / 10) % 100,2); //conversion in hundredths
			break;
		case TIMEUNIT_SECONDS:
			seconds = FormatNumber((ticks / 1000) % 60,2); //conversion into seconds
			break;
		case TIMEUNIT_MINUTES:
			minutes = FormatNumber((ticks / 60000) % 60,2); //conversion into minutes
			break;
		case TIMEUNIT_HOURS:
			hours = FormatNumber(ticks / 3600000, 2); //conversion into hours
			break;
		}
	}
	sprintf(result, "%s:%s:%s:%s'", hours, minutes, seconds, hundreths);
	return result;
}
char* timeString(Uint32 offset)
{
	Uint32 ticks = SDL_GetTicks() - offset;
	return FormatNumber(ticks, 0);
}



/* obsolete function */
/* for program exiting, cleaning and freeing up memory */
void clear()
{
	closeSeconds();

	/* Closing the font */
	TTF_CloseFont (time);
}


void levelOneSetup()
{
	sprite_t * bglvl1_1 = load("graphic/level/bg/newbg.png", 32, 32);

	bglvl1_1->background = 1;

	initPlayer ();

	//loadLevel ("level 1");

	//setLvlState (JEKYLL_MODE);

	initHUD ();

	start = SDL_GetTicks();

	running = true;

	if (space != NULL && getPlayer() != NULL)
	{
		if (!getPlayer()->body) return;
		if (!getPlayer()->shape) return;
		//printf("AZIZ LIGHT\n");
		cpSpaceAddBody(space, getPlayer()->body);
		cpSpaceAddShape(space, getPlayer()->shape);
	}

	spawnMultiParticle (30, 40, 12);
}

void levelTwoSetup()
{
	sprite_t * bglvl2_1 = load("graphic/level/bg/newbglvl1_1.png", 32, 32);

	bglvl2_1->background = 1;

	initPlayer ();

	//loadLevel ("level 2");

	setLvlState (HYDE_MODE);

	getPlayer()->currentAnger = 99;

	initHUD ();

	start = SDL_GetTicks();

	running = true;

	if (space != NULL && getPlayer() != NULL)
	{
		if (!getPlayer()->body) return;
		if (!getPlayer()->shape) return;
		//printf("AZIZ LIGHT\n");
		cpSpaceAddBody(space, getPlayer()->body);
		cpSpaceAddShape(space, getPlayer()->shape);
	}
}

void levelEditSetup()
{
	/*
	spawned = 0;

	sprite_t * lvlEditBg = NULL;

	lvlEditBg = load("graphic/level/bg/newbglvl1_1.png", 32 , 32);
	lvlEditBg->background = 1;

	mouseSprite = load ("graphic/game/mouse.png", 32, 32);
	if (mouseSprite == NULL)
		printf("mouse didn't load\n", IMG_GetError());

	testTile = load("graphic/level/lvldesign/plvl_1.png", 62, 24);
	if (testTile == NULL)
		printf("testtile didn't load\n", IMG_GetError());

	loadLevel ("custom level");

	fp = fopen("data/level/lvlEdit.json", "w");
	if (fp == NULL)
		fprintf(stderr, "can't open json file");

	setLvlState (JEKYLL_MODE);
	*/
}

void customLevelSetup()
{
	sprite_t * bglvl2_1 = load("graphic/level/bg/newbglvl1_1.png", 32, 32);

	bglvl2_1->background = 1;

	initPlayer ();

	//loadLevel ("custom level");

	setLvlState (JEKYLL_MODE);

	getPlayer()->currentAnger = 1;

	initHUD ();

	start = SDL_GetTicks();

	running = true;

	if (space != NULL && getPlayer() != NULL)
	{
		if (!getPlayer()->body) return;
		if (!getPlayer()->shape) return;
		//printf("AZIZ LIGHT\n");
		cpSpaceAddBody(space, getPlayer()->body);
		cpSpaceAddShape(space, getPlayer()->shape);
	}
}

void gameOverSetup()
{
	sprite_t * bglvl2_1 = load("graphic/game/gameover.png", 32, 32);
	bglvl2_1->background = 1;

	setLvlState (NO_MODE);

	start = 0;

	running = false;
}

cpSpace * getSpace()
{
	return space;
}

int getSpawned()
{
	return spawned;
}