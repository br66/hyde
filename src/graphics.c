#include "include.h"

static SDL_Surface *screen = NULL; //#sprite

static SDL_Surface listSprites[MAX_SPRITES]; //#sprite

/**********************************************************************************************//**
 * @fn	SDL_Surface *load_Image (char *filename)
 *
 * @brief	Loads an image, this is from the tutorials, those dirty inefficient tutorials.
 *
 * @author	iwh
 * @date	4/14/2015
 *
 * @param [in,out]	filename	If non-null, filename of the file.
 *
 * @return	null if it fails, else the image.
 **************************************************************************************************/
//#sprite
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

//#sprite
/* this is heavily based off of dj's code */
sprite_t* load (char *filename, int width, int height)
{
	/* will replace with searching thru list of loaded sprites */
	/* 
		for (i = 0; i < numSprites, i++)
		{
			if (strncmp(filename, listSprites[i].filename, 20) == 0)
			{
				listSprites[i].used++;
				return &listSprites[i];
			}
		}
	*/

	/* do we have room? */
	/*
		if(numSprites + 1 >= MAX_SPRITES)
		{
			//too many sprites too many sprites too many sprites
		}
	*/

	/* you made it this far kid, now time for the real stuff */
	/*
		numSprites++;
		for (i=0; i <= numSprites; i++)
			if(!spritelist[i].used)break; //if i find one that isn't used break 
		
		//temporary pointer for getting an address = img_load(filename);

		spritelist[i].image = this image
		// setting [i]'s image

		strncpy(spritelist[i].filename, filename, 20)
		// setting [i]'s filename

		[i].framesperline = 16
		[i].w = width;
		[i].h = height;
		[i].used++;
		return the address;
	}
	*/
}

//#sprite
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

//#sprite
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

	SDL_BlitSurface (spritesheet, &source, surface, &dest); //#sprite
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

//#sprite
SDL_Surface* getScreen (void)
{
	return screen;
}
//#sprite
void closeScreen(void)
{
	SDL_FreeSurface (screen);
}

// frame = (frame + 1) % 16
// nextthink = 500 + currentTime;