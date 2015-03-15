#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "boolean.h"
#include "gfunc.h"
#include "graphics.h"
#include "entity.h"

SDL_Surface *screen = NULL;		// application window
SDL_Surface *bgSprite = NULL; // surface that will be background

SDL_Surface *upMessage = NULL;	// surfaces for loading/showing a notice on the screen that a key has been pressed
SDL_Surface *downMessage = NULL;
SDL_Surface *leftMessage = NULL;
SDL_Surface *rightMessage = NULL;

SDL_Surface *message = NULL;

SDL_Surface *seconds = NULL;

SDL_Rect health;
SDL_Rect anger;

/* object sprites */
SDL_Surface *bombSprite = NULL;

/* Telling the game that we will be using a font, defined in gfunc.c */
TTF_Font *font = NULL;

/* Telling the game what font the color will be  In this case, white */
SDL_Color textColor = { 255, 255, 255 };

/* Telling the game I will have a music file */
Mix_Music *music= NULL;

/* Telling the game I will have sound effects */
Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;

//objects
SDL_Surface *dot = NULL;

//Keep track of the frame count
int frameCount;

SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

/* For events (ex. key presses) */
SDL_Event event;

bool init() // Start everything
{
	//Initialize SDL and checks if it did it successfully
	/*SDL's subsystems (video, audio, timers, engine components) are started up */
	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
	{
		return false;
	}

	/* If this loads correctly, we can use TrueType Fonts (TTF). */
	if ( TTF_Init() == -1 )
	{
		return false;
	}

	/* If this loads correctly, we can have music */
	if (Mix_OpenAudio ( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		return false;
	}

	//Set up the screen and check if it did it successfully
	/*Fourth argument creates the screens surface in system memory */
	screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, BITSPERPIXEL, SDL_SWSURFACE);
	if (screen == NULL)
	{
		return false;
	}

	/* Setting the window title */
	SDL_WM_SetCaption ("Game", NULL);

	/* If I didn't screw up anything, return true. */
	return true;
}

/* For loading the files all at once, foreshadow to precaching? */
bool load_Files()
{
	bgSprite = load_Image("sprite/sky1.png");
	if (bgSprite == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	dot = load_Image("sprite/square.bmp");
	if (dot == NULL)
	{
		return false;
	}

	font = TTF_OpenFont ("font/lazy.ttf", 28);
	if (font == NULL)
	{
		return false;
	}

	music = Mix_LoadMUS ("sound/beat.wav");
	if (music == NULL )
	{
		return false;
	}

	/* Telling the game what the sound effects will actually be */
	scratch = Mix_LoadWAV ( "sound/scratch.wav" );
	high = Mix_LoadWAV ( "sound/high.wav" );
	med = Mix_LoadWAV ( "sound/medium.wav" );
	low = Mix_LoadWAV ( "sound/low.wav" );
	if ((scratch == NULL) || (high == NULL) || (med == NULL) || (low == NULL))
	{
		return false;
	}

	bombSprite = load_Image("sprite/bomb.png");

	return true;
}

/* Rough translation of timecode, will attempt to better clarify later */

char *FormatNumber(Uint32 number, int min)
{
	Uint32 value = number;  //The number we get from the raw time (which is in U32 form)
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
char* timeString(Uint32 offset) //not used
{
	Uint32 ticks = SDL_GetTicks() - offset;
	return FormatNumber(ticks, 0);
}

void set_Camera (entity_t *ent)
{
	int xmargin;
	xmargin = 1000;

	camera.x = ( ent->bBox.x + ent->width + xmargin / 2) - L_WIDTH / 2;
	camera.y = ( ent->bBox.y + ent->height / 2) - L_HEIGHT / 2;

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
	SDL_FreeSurface (upMessage);
	SDL_FreeSurface (downMessage);
	SDL_FreeSurface (leftMessage);
	SDL_FreeSurface (rightMessage);
	SDL_FreeSurface (message);
	SDL_FreeSurface (bgSprite);

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
