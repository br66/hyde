#include <SDL.h>
#include <SDL_ttf.h>

#include "boolean.h"
#include "gfunc.h"
#include "graphics.h"

#define CLIP_MOUSEOVER	0 //for buttons
#define CLIP_MOUSEOUT	1
#define CLIP_MOUSEDOWN	2
#define CLIP_MOUSEUP	3

SDL_Surface *screen = NULL;		// application window
SDL_Surface *background = NULL; // surface that will be background

SDL_Surface *upMessage = NULL;	// surfaces for loading/showing a notice on the screen that a key has been pressed
SDL_Surface *downMessage = NULL;
SDL_Surface *leftMessage = NULL;
SDL_Surface *rightMessage = NULL;

SDL_Surface *message = NULL;

SDL_Rect clips[ 4 ]; //rectangle for breaking the image into sections

/* Telling the game that we will be using a font, defined in gfunc.c */
TTF_Font *font = NULL;

/* Telling the game what font the color will be  In this case, white */
SDL_Color textColor = { 255, 255, 255 };

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

	/* If this loads correctly, we can use TrurType Fonts (TTF). */
	if ( TTF_Init() == -1 )
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

	return true;
}

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
	clips[CLIP_MOUSEDOWN].w = 320;
	clips[CLIP_MOUSEDOWN].h = 240;

	clips[CLIP_MOUSEUP].x = 320;
	clips[CLIP_MOUSEUP].y = 240;
	clips[CLIP_MOUSEUP].w = 320;
	clips[CLIP_MOUSEUP].h = 240;
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
	SDL_FreeSurface (background);

	/* Closing the fonts and text engine */
	TTF_CloseFont (font);
	TTF_Quit();

	//Will free the screen surface and close SDL
	SDL_Quit();
}
