#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "boolean.h"
#include "gfunc.h"
#include "graphics.h"

//#define CLIP_MOUSEOVER	0 //for buttons
//#define CLIP_MOUSEOUT	1
//#define CLIP_MOUSEDOWN	2
//#define CLIP_MOUSEUP	3

SDL_Surface *screen = NULL;		// application window
SDL_Surface *background = NULL; // surface that will be background

SDL_Surface *upMessage = NULL;	// surfaces for loading/showing a notice on the screen that a key has been pressed
SDL_Surface *downMessage = NULL;
SDL_Surface *leftMessage = NULL;
SDL_Surface *rightMessage = NULL;

SDL_Surface *message = NULL;

SDL_Surface *seconds = NULL;

SDL_Rect clips[ 4 ]; //rectangle for breaking the image into sections

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
	/*LOADING BACKGROUND */
	background = load_Image("sprite/tree.bmp");
	if (background == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	/* LOADING SPRITESHEET
	sheet = load_Image("sprite/dots.png");
	if (sheet == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	} 
	*/

	/* LOAD TEH FONT */
	// Telling the game what the font is and the font size
	font = TTF_OpenFont ("font/lazy.ttf", 28);
	if (font == NULL)
	{
		return false;
	}

	/* Telling the game what the music will be */
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

	return true;
}


char *FormatNumber(Uint32 number, int min)
{
	Uint32 value = number;
	static char array[10][20];  //making an array of arrays
	static int buffer = 0; //creating a buffer, saving the numbers
	int count, x;

	buffer = (buffer + 1) % 10; //moves to the next spot in array? makes sure it doesn't go outside of 0-9?f

	/* Unsigned integers should not be converted into char,
	therefore, we will count.  Everytime we get a number, we
	will increment the count */
	for (count = 0; value != 0; count++)
		value /= 10;
	if(count < min)
		count = min;
	for (x = count; x > 0; x--) // we will count 9 times 
	{
		array[buffer][x-1] = '0' + number % 10; //array length - 1 is entry in array, we find last number in uint32 ticks;
		number /= 10; //move on to the next number in uint32 ticks, keep doing this until x = 0;
	}
	if(count == 0){
		array[buffer][count] = '0';
		count++;
	}
	array[buffer][count] = '\0'; //use length of array to find end of array, make it \0, will signify end of array
	return array[buffer];
}

#define TIMEUNIT_HOURS		3
#define TIMEUNIT_MINUTES	2
#define TIMEUNIT_SECONDS	1
#define TIMEUNIT_HUNDRETHS	0

char* FormatTimeString(Uint32 offset) //creates result var, converts raw time into h/m/s time and retruns it
{
	static char result[80];
	int i;
	char *hundreths, *seconds, *minutes, *hours;
	Uint32 ticks = SDL_GetTicks() - offset;
	Uint32 num = ticks;
	for(i = 0;i <= TIMEUNIT_HOURS;i++){
		switch(i){
		case TIMEUNIT_HUNDRETHS:
			hundreths = FormatNumber((ticks / 10) % 100,2);
			break;
		case TIMEUNIT_SECONDS:
			seconds = FormatNumber((ticks / 1000) % 60,2);
			break;
		case TIMEUNIT_MINUTES:
			minutes = FormatNumber((ticks / 60000) % 60,2);
			break;
		case TIMEUNIT_HOURS:
			hours = FormatNumber(ticks / 3600000,2);
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


/*
void set_Clips() // for buttons
{
	clips[CLIP_MOUSEOVER].x = 0;
	clips[CLIP_MOUSEOVER].y = 0;
	clips[CLIP_MOUSEOVER].w = 320;
	clips[CLIP_MOUSEOVER].h = 240;

	clips[CLIP_MOUSEOUT].x = 320;
	clips[CLIP_MOUSEOUT].y = 0;
	clips[CLIP_MOUSEOUT].w = 320;
	clips[CLIP_MOUSEOUT].h = 240;

	clips[CLIP_MOUSEDOWN].x = 0;
	clips[CLIP_MOUSEDOWN].y = 240;
	clips[CLIP_MOMOUUSEDOWN].w = 320;
	clips[CLIP_SEDOWN].h = 240;

	clips[CLIP_MOUSEUP].x = 320;
	clips[CLIP_MOUSEUP].y = 240;
	clips[CLIP_MOUSEUP].w = 320;
	clips[CLIP_MOUSEUP].h = 240;
}
*/

/* for program exiting, cleaning and freeing up memory */
void clear()
{
	/* Freeing up memory by getting rid of these surfaces (images) */
	SDL_FreeSurface (upMessage);
	SDL_FreeSurface (downMessage);
	SDL_FreeSurface (leftMessage);
	SDL_FreeSurface (rightMessage);
	SDL_FreeSurface (message);
	SDL_FreeSurface (background);

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
