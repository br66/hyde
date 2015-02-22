#include <SDL.h>

#define	SCREEN_WIDTH	640
#define	SCREEN_HEIGHT	480
#define	BITSPERPIXEL	32

SDL_Surface *load_Image (char *filename);											/* Load Image from file function:  Takes an image by filename and optimizes it for the screen */
void show_Surface (int x, int y, SDL_Surface* source, SDL_Surface* destination);	/* Displaying Image function: Shows image on a given surface; makes image visible */