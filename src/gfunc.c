/* Functions called in the game loop */

#include "include.h"

static SDL_Surface *seconds = NULL;

static SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

static TTF_Font *font = NULL;

static Uint32 currentTime = 0;

extern int level;

extern SDL_Event event;

extern SDL_Rect health; //to replace with getCurHealth();
extern SDL_Rect anger; //to replace with getCurAnger();

extern entity_t *enemy1;
extern entity_t *enemy2;
extern entity_t *enemy3;

extern bool done;
extern bool running;

extern Uint32 start;

level_t levels[10];

SDL_Surface *bgSprite = NULL;
SDL_Surface *bgSprite2 = NULL;

Mix_Music *music= NULL;
Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;

SDL_Surface *plyrSprite = NULL;
SDL_Surface *bombSprite = NULL;
SDL_Surface *bossSprite = NULL;

SDL_Surface *platformSprite1 = NULL;
SDL_Surface *platformSpriteA1 = NULL;

level_t *stage1 = NULL;
level_t *stage2 = NULL;

extern entity_t *platform1;
extern entity_t *platform2;
extern entity_t *platformA1;
extern entity_t *platformA2;

bool init()
{
	/* start SDL 1.2 */
	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
	{
		return false;
	}

	/* fonts for text */
	if ( TTF_Init() == -1 )
	{
		return false;
	}

	/* music */
	if (Mix_OpenAudio ( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		return false;
	}

	/* Fourth argument creates the screens surface in system memory */
	if (setUpScreen() == false)
	{
		return false;
	}


	/* Window title */
	SDL_WM_SetCaption ("Game", NULL);

	/* If nothing's wrong, return true. */
	return true;
}

/* Loads all files in one function, foreshadow to precaching? */
bool load_Files()
{
	/* lvl 1 sprites */
	//put into list first [listSprites]
	bgSprite = load_Image("sprite/sky1.png");
	if (bgSprite == NULL)
	{
		printf("error: %s\n", SDL_GetError());
		return false;
	}

	bgSprite2 = load_Image("sprite/sky2.png");
	if (bgSprite2 == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}
	platformSprite1 = load_Image("sprite/lvl/platform1.png");
	if (platformSprite1 == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	platformSpriteA1 = load_Image("sprite/lvl/platform2.png");
	if (platformSpriteA1 == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	/* player sprite */
	plyrSprite = load_Image("sprite/char/jekyll_sheet.png");
	if (plyrSprite == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	/* enemy sprites */
	bombSprite = load_Image("sprite/laserRed09.png");
	if (bombSprite == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	bossSprite = load_Image("sprite/boss.png");
	if (bossSprite == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	/* font */
	font = TTF_OpenFont ("font/lazy.ttf", 28);
	if (font == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	/* audio */
	music = Mix_LoadMUS ("sound/beat.wav");
	if (music == NULL )
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	/* sound effects */
	scratch = Mix_LoadWAV ( "sound/scratch.wav" );
	high = Mix_LoadWAV ( "sound/high.wav" );
	med = Mix_LoadWAV ( "sound/medium.wav" );
	low = Mix_LoadWAV ( "sound/low.wav" );
	if ((scratch == NULL) || (high == NULL) || (med == NULL) || (low == NULL))
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}
	return true;
}

/* Check level function - show corresponding level */
void CheckLevel ()
{
	stage1 = &levels[0];

	sprintf(stage1->level, "stage 1");
	stage1->backgrounds[0] = bgSprite;

	stage1->lvlEntities[0] = platform1;
	stage1->lvlEntities[2] = platform1;
	stage1->lvlEntities[3] = platform2;
	stage1->lvlEntities[4] = platform2;
	//---------------------------------
	stage2 = &levels[1];

	sprintf(stage2->level, "stage 2");
	stage2->backgrounds[0] = bgSprite2;

	stage2->lvlEntities[1] = platformA1;
	stage1->lvlEntities[2] = platformA1;
	stage1->lvlEntities[3] = platformA2;
	stage1->lvlEntities[4] = platformA2;

	if (level == 1)
	{
		show_LevelOne();

	}
	if (level == 2)
	{
		show_LevelTwo();
	}
}

/* Rough translation of timecode, will attempt to better clarify later */
char *FormatNumber(Uint32 number, int min)
{
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

#define TIMEUNIT_HOURS		3
#define TIMEUNIT_MINUTES	2
#define TIMEUNIT_SECONDS	1
#define TIMEUNIT_HUNDRETHS	0

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

void set_Camera (entity_t *ent)
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

/* for program exiting, cleaning and freeing up memory */
void clear()
{
	/* Freeing up memory by getting rid of these surfaces (images) */
	//SDL_FreeSurface (message);
	
	SDL_FreeSurface (bgSprite);
	SDL_FreeSurface (platformSprite1);
	SDL_FreeSurface (platformSpriteA1);
	SDL_FreeSurface (bombSprite);
	SDL_FreeSurface (bossSprite);
	SDL_FreeSurface (plyrSprite);

	closeSeconds();
	closeScreen();

	/* Closing the fonts and text engine */
	TTF_CloseFont (font);
	TTF_Quit();

	/* Getting the audio out of memory */
	Mix_FreeChunk (scratch);
	Mix_FreeChunk (high);
	Mix_FreeChunk (med);
	Mix_FreeChunk (low);

	Mix_FreeMusic (music);

	/* Close Audio engine */
	Mix_CloseAudio();

	//Will free the screen surface and close SDL
	SDL_Quit();
}

SDL_Rect getCamera (void)
{
	return camera;
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
	seconds = TTF_RenderText_Solid (getFont(), msg, textColor); //setUpSeconds();
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

void UpdateHealth()
{
	health.w = (getPlayer()->currentHealth * 100) / getPlayer()->max_health; //how do I get rid of division? can I

	if (getPlayer()->currentHealth == 0)
	{
		//sprite that says game over
		printf("game over");
	}
}

void UpdateAnger()
{
	anger.w = (getPlayer()->currentAnger * 100) / getPlayer()->maxAnger; //how do I get rid of division? can I

	if (getPlayer()->currentAnger >= 100)
	{
		printf("level switch to #2");

		level = 2;

		getPlayer()->currentAnger = 99;
		getPlayer()->x = 0;
		getPlayer()->y = 340;
	}
}

void Events()
{
	while (SDL_PollEvent (&event))
		{
			handle_Input(getPlayer());

			if ( event.type == SDL_KEYDOWN )
			{
				switch ( event.key.keysym.sym )
				{
					case SDLK_1:
						if (level != 1)
						{
							level = 1;

							//enemy 1 initial position
							enemy1->x = 600;
							enemy1->y = 350;
							enemy1->thinkflags = 0;
							enemy1->xVel = 0;

							//enemy 2 initial position
							enemy2->x = 770;
							enemy2->y = 350;
							enemy2->thinkflags = 0;
							enemy2->xVel = 0;

							//enemy 3 initial position
							enemy3->x = 900;
							enemy3->y = 350;
							enemy3->thinkflags = 0;
							enemy3->xVel = 0;
							enemy3->yVel = 0;

							//boss 3 initial position
							//boss->x = 1000;
							//boss->y = 300;
							//boss->thinkflags = 0;
							//boss->xVel = 0;
							//boss->yVel = 0;
							//playerAnimSet = animationFile("animation\\player.json") or animationFile(player);
						}
						break;
					case SDLK_2:
						if (level != 2)
						{
							level = 2;

							//enemy 1 initial position, just in case
							enemy1->x = 600;
							enemy1->y = 350;
							enemy1->thinkflags = 0;
							enemy1->xVel = 0;

							//enemy 2 initial position, just in case
							enemy2->x = 770;
							enemy2->y = 350;
							enemy2->thinkflags = 0;
							enemy2->xVel = 0;

							//enemy 3 initial position, just in case
							enemy3->x = 900;
							enemy3->y = 350;
							enemy3->thinkflags = 0;
							enemy3->xVel = 0;
							enemy3->yVel = 0;

							//boss 3 initial position
							//boss->x = 1000;
							//boss->y = 300;
							//boss->thinkflags = 0;
							//boss->xVel = 0;
							//boss->yVel = 0;
						}
						break;
					case SDLK_s:
						if (running == true)
						{
							running = false;
							start = 0;
						}
						else
						{
							running = true;
							start = SDL_GetTicks();
						}
					}
				}

			if(event.type == SDL_QUIT)
			{
				done = true;
			}
		}
}