/**********************************************************************************************//**
 * @file	src\graphics.h
 *
 * @brief	Declares the graphics class.  Used for loading graphics and showing them and setting
 * 			up and closing the screen.  The screen is that of which all objects will render to.
 **************************************************************************************************/

#ifndef _GRAPHICS_
#define _GRAPHICS_

#include <SDL.h>

#define	SCREEN_WIDTH	640 
#define	SCREEN_HEIGHT	480

#define	BITSPERPIXEL	32

#define L_WIDTH			1920
#define	L_HEIGHT		1200

#define MAX_SPRITES  50

/* Load Image from file function:  Takes an image by filename and optimizes it for the screen */
SDL_Surface *load_Image (char *filename);

/* Displaying Image function: Shows image on a given surface; makes image visible */
void show_Surface (float x, float y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void showFrame (SDL_Surface* spritesheet, SDL_Surface* surface, float sx, float sy, int frame);

/* SCREEN */
bool setUpScreen (void);
SDL_Surface* getScreen (void);
void closeScreen(void);

#endif