#include "include.h"

static SDL_Surface *screen = NULL;

static SDL_Surface listSprites[MAX_SPRITES];

/**********************************************************************************************//**
 * @fn	SDL_Surface *load_Image (char *filename)
 *
 * @brief	Loads an image, optimized to be displayed properly.
 *
 * @author	iwh
 * @date	4/14/2015
 *
 * @param [in,out]	filename	If non-null, filename of the file.
 *
 * @return	null if it fails, else the image.
 **************************************************************************************************/

SDL_Surface *load_Image (char *filename) /* Load Image from file function */
{
	SDL_Surface* loadedImage = NULL; /* this will be image from parameter */

	SDL_Surface* finalImage = NULL; /* this will be vers. of image optimized for game */

	loadedImage = IMG_Load(filename); /* we know have image from parameter */

	if( loadedImage != NULL) /* if that filename is not fradulent */
	{
		finalImage = SDL_DisplayFormat( loadedImage ); /* we now make optimized image */ //displayformatAlpha?

		SDL_FreeSurface (loadedImage); /* get rid of the old version */

		if (finalImage != NULL) /* if final image is not fradulent */
		{
			Uint32 colorkey = SDL_MapRGB( finalImage->format, 0, 0xFF, 0xFF ); /* designate a color that we will take out of the image */
			
			SDL_SetColorKey (finalImage, SDL_SRCCOLORKEY, colorkey); /*Take the optimized image (1st argument), take this color (3rd argument) out of it. */

			/* 2nd argument exists because the "SetColorKey" function can do other things other than get rid of a color. */
		}
	}
	return finalImage; /* send out finalized image */
}

/* Displaying Image function */
void show_Surface (float x, float y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	//Temporary rectangle used to tell function where to display source surface on screen
	SDL_Rect offset;

	//Taking in the positions given to the function
	offset.x = (int)x;
	offset.y = (int)y;

	//Displaying the surface
	SDL_BlitSurface( source, clip, destination, &offset);
}

void showFrame (SDL_Surface* spritesheet, SDL_Surface* surface, float sx, float sy, int frame) // to get entity and its framesperline for its sprite
{
	SDL_Rect source, dest;

	source.x = (frame * 32) % 320;
	source.y = (frame * 32) / 320;
	source.w = 32;
	source.h = 32;

	dest.x = (int)sx;
	dest.y = (int)sy;
	dest.w = 32;
	dest.h = 32;

	SDL_BlitSurface (spritesheet, &source, surface, &dest); //1. source, clip, dest, clip
}

bool setUpScreen()
{
	screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, BITSPERPIXEL, SDL_SWSURFACE);
	if (screen == NULL)
	{
		return false;
	}
	return true;
}
SDL_Surface* getScreen (void)
{
	return screen;
}
void closeScreen(void)
{
	SDL_FreeSurface (screen);
}

/* depreciated
void animIdle (entity_t *ent)
{
	ent->frame = (ent->frame + 1) % 16;
	ent->animThink = getCurrentTime() + 500;
}
*/
// frame = (frame + 1) % 16
// nextthink = 500 + currentTime;