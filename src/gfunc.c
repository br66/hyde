/* Variables needed here are declared here and usually only used
here if not by a get or set function.  Spritesheet was being
edited so for now the player's frame will be a white square. */

/* Functions called in the game loop */

#include "include.h"

static SDL_Surface *seconds = NULL;

static SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

static TTF_Font *font = NULL;

static Uint32 currentTime = 0;

SDL_Surface *bgSprite = NULL;
SDL_Surface *bgSprite2 = NULL;
//SDL_Surface *message = NULL;

Mix_Music *music= NULL;
Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;

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