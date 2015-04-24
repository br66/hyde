/**********************************************************************************************//**
 * @file	src\graphics.h
 *
 * @brief	Declares the graphics/sprite class.  Used for loading graphics and showing them and setting
 * 			up and closing the screen.  The screen is that of which all objects will render to.
 **************************************************************************************************/

#ifndef _GRAPHICS_
#define _GRAPHICS_

#define	SCREEN_WIDTH	640 
#define	SCREEN_HEIGHT	480

#define	BITSPERPIXEL	32

#define L_WIDTH			1920
#define	L_HEIGHT		1200

#define MAX_SPRITES  50

#include <SDL.h> //do i need this?
#include "animation.h"

/* Sprite Structure */
typedef struct sprite_s
{
	SDL_Surface		*graphic; //can be a single sprite or a spritesheet
	animSet_t		*animationSet; //each sprite has a set of animaitions associated with it
	char			filename[30];
	int				width, height;
	int				framesperline;
	int				used; //reference count

}sprite_t;

/* load image - takes an image by filename and optimizes it for the screen, will be depreciated by below function. */
SDL_Surface *load_Image (char *filename);
/* sprite load - will load a sprite from filename, keep that filename for future functions, find, load, and optimize sprite/spritesheet for usage */
sprite_t* load (char *filename, int width, int height);

/* Displaying image function: Shows image on a given surface; makes image visible */
void show_Surface (float x, float y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void showFrame (SDL_Surface* spritesheet, SDL_Surface* surface, float sx, float sy, int frame);

/* SDL_Surface *screen */
bool setUpScreen ();
SDL_Surface* getScreen ();
void closeScreen ();

/* For all sprites/graphics/spritesheets */
void initSpriteList ();
void closeSpriteList ();
sprite_t* loadSprite (char *filename, int width, int height);
#endif