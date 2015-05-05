/* companion to game.c file */

#include <jansson.h>
#include "include.h"
#include "spawn.h"

game_t Game;

static SDL_Surface *seconds = NULL;
static SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
static TTF_Font *font = NULL;
static Uint32 currentTime = 0;
static bool running = true;

// for events
SDL_Event event;

//extern SDL_Rect health; //to replace with getCurHealth();
//extern SDL_Rect anger; //to replace with getCurAnger();

extern bool done;
extern Uint32 start;

// for beginning of game
void begin()
{
	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
		printf("SDL 1.2 error \n", SDL_GetError());
	else printf("sdl init success \n");

	if (Mix_OpenAudio ( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
		printf("SDL Mixer error \n", SDL_GetError());
	else printf("sdl mixer success \n");

	if ( TTF_Init() == -1 )
		printf("SDL TTF error \n", SDL_GetError());
	else printf("sdl ttf success \n");

	/* graphics/sprites */
	initSprites();
	if (setupScreen() == false)
		printf("problem setting up screen \n", SDL_GetError());
	else printf("screen is set up \n");

	/* entities */
	initEntities();

	//begin() - initiates basic utilities for game to run
		
		/*
		<< SDL 1.2
		< graphics/spritelist
		<< audio/soundlist
		<< font
		<< entity
		<< mainmenu()/splash screen, same?
		< precache sound
		*/

		/*
		particles
		HUD? not now
		drawlevel?
		*/

	//start the game at the menu
	setGameState(GSTATE_MENU);
	setLvlState(NO_MODE);
	SDL_WM_SetCaption ("HYDE", NULL);

}

// for end of game
void end()
{
	Mix_CloseAudio();
	TTF_Quit();
	closeScreen();
	closeSprites();
	closeEntities();
	SDL_Quit();
	//destroy everything
}

// for setting the game state
void setGameState(int gameState)
{
	if (Game.gameState = gameState)
		return;
	else
		Game.gameState = gameState;
}

// for setting the game state
void setLvlState (int levelState)
{
	if (Game.levelState = levelState)
		return;
	else
		Game.levelState = levelState;
}

void loadLevel(char * level)
{
	int i, j;
	char *filename = NULL;

	json_t * parser;
	json_error_t error; // error handler

	json_t *data, *name, *background, *lvlpieces, *entity;
	json_t *classname, *flag, *x, *y;

	// can't case switch strings :/
	if (strcmp(level, "level 1") == 0)
	{
		printf("loading level one\n");
		sprintf(level, "data\\level\\level1.json");
	}
	
	if (strcmp(level, "level 2") == 0)
	{
		printf("loading level two");
		sprintf(level, level);
		return;
	}

	if (strcmp(level, "boss 1") == 0)
	{
		printf("loading boss 1");
		sprintf(level, level);
		return;
	}

	// loading the file
	parser = json_load_file(level, 0, &error);
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
	//printf("%s \n", json_string_value(name));

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
			fprintf(stderr, "i was looking for the array of entities");
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
		//printf("%s\n", json_string_value(classname));

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
	printf("file data succesfully loaded");
	return;
}

/* gets, sets, and closers to reduce amount of externs */
SDL_Rect getCamera (void)
{
	return camera;
}

void cameraSetOn (entity_t *ent)
{
	int xmargin;
	xmargin = 1000;

	camera.x = ( (int)ent->x + ent->width + xmargin / 2) - L_WIDTH / 2;
	camera.y = ( (int)ent->y + ent->height / 2) - L_HEIGHT / 2;

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
	return font;
}

Uint32 getCurrentTime(void)
{
	return currentTime;
}
void setCurrentTime(void)
{
	currentTime = SDL_GetTicks();
}

SDL_Surface *getSeconds(void)
{
	return seconds;
}

void setUpSeconds(char* msg, SDL_Color textColor) //where to render to and what color
{
	seconds = TTF_RenderText_Solid (getFont(), msg, textColor);
	show_Surface ((SCREEN_WIDTH - (float)seconds->w ) / 2, 50, seconds, getScreen(), NULL);

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

// for the player and hud
/*void UpdateHealth()
{
	health.w = (getPlayer()->currentHealth * 100) / getPlayer()->max_health; //how do I get rid of division? can I

	if (getPlayer()->currentHealth < 0)
	{
		surface(gameOver, getScreen(), 0, 0, NULL);
		//printf("game over");
	}
}*/

/*void UpdateAnger()
{
	anger.w = (getPlayer()->currentAnger * 100) / getPlayer()->maxAnger; //how do I get rid of division? can I

	if (getPlayer()->currentAnger >= 100)
	{
		//printf("level switch to #2 \n");

		level = 2;

		getPlayer()->currentAnger = 99;
		getPlayer()->x = 0;
		getPlayer()->y = 340;
	}
}*/

// for game events (ex. keyboard input)
// reminder: put player in level file
void Events()
{
	while (SDL_PollEvent (&event))
	{
			if ( event.type == SDL_KEYDOWN )
			{
				switch ( event.key.keysym.sym )
				{
					case SDLK_m:
						setGameState(GSTATE_MENU);
						break;
					case SDLK_l:
						setGameState(GSTATE_LEVELEDIT); printf("got here\n");
						break;
					case SDLK_1:
						setGameState(GSTATE_LEVEL1); printf("got here too\n");
						break;
					case SDLK_UP:
						{
							if(getPlayer() != NULL)
								getPlayer()->yVel -= getPlayer()->height >> 4; 
							break;
						}
					case SDLK_DOWN:
						{
							if(getPlayer() != NULL)
								getPlayer()->yVel += getPlayer()->height >> 4;
							break;
						}
					case SDLK_LEFT:
						{
							if(getPlayer() != NULL)
								getPlayer()->xVel -= getPlayer()->width >> 4;
							break;
						}
					case SDLK_RIGHT: 
						{
							if(getPlayer() != NULL)
								getPlayer()->xVel += getPlayer()->width >> 4; 
							break;
						}
				}

			}
			else if (event.type == SDL_KEYUP)
			{
				switch ( event.key.keysym.sym )
				{
					case SDLK_UP:
						{
							if(getPlayer() != NULL)
								getPlayer()->yVel += getPlayer()->height >> 4; 
							break;
						}
					case SDLK_DOWN:
						{
							if(getPlayer() != NULL)
								getPlayer()->yVel -= getPlayer()->height >> 4; 
							break;
						}
					case SDLK_LEFT:
						{
							if(getPlayer() != NULL)
								getPlayer()->xVel += getPlayer()->width >> 4;
							break;
						}
					case SDLK_RIGHT:
						{
							if(getPlayer() != NULL)
								getPlayer()->xVel -= getPlayer()->width >> 4; 
							break;
						}
				}
			}

			if (event.type == SDL_QUIT)
			{
				done = true; // to call functions to prepare to close game
				setGameState(-1); // don't know if this is safe..
			}
	}
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
	static char result[80]; /* ??? */
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
	TTF_CloseFont (font);
}

// new - may replace some existing functions
void events()
{
	/* if state is splash
		do this */

	/* if state is level1
		do this */
}

void draw()
{
	//draw
}

void think() //also known as update
{
	//update
}