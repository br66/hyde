#ifndef _GRAPHICS_
#define _GRAPHICS_

#include <SDL.h>
#include "entity.h" //SHOWFRAME WILL BE EDITED TO REMOVE THIS LINE

#define	SCREEN_WIDTH	640 
#define	SCREEN_HEIGHT	480

#define	BITSPERPIXEL	32

#define L_WIDTH			1920
#define	L_HEIGHT		1200

/* Load Image from file function:  Takes an image by filename and optimizes it for the screen */
SDL_Surface *load_Image (char *filename);

/* Displaying Image function: Shows image on a given surface; makes image visible */
void show_Surface (float x, float y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void showFrame (entity_t* ent, SDL_Surface* surface, float sx, float sy, int frame);

/* SCREEN */
bool setUpScreen (void);
SDL_Surface* getScreen (void);
void closeScreen(void);

#endif