#include <SDL.h>

/* Load Image from file function */
SDL_Surface *load_Image (char *filename)
{
	//temporarily store the image here
	SDL_Surface* loadedImage = NULL;

	//because we need to optimize it
	SDL_Surface* finalImage = NULL;

	//we are going to take an image in as a parameter
	//and return a pointer to the optimized vers.

	//getting the image from the file system
	//attaching an address to the pointer
	loadedImage = SDL_LoadBMP(filename);

	//if my pointer is not null / if i was able to get the image successfully
	if( loadedImage != NULL)
	{
		//we will optimize the image for SDL
		//this will create a new version of the image
		//in the same format as the screen
		finalImage = SDL_DisplayFormat( loadedImage );

		//the "loadedImage" has been optimized for showing now
		//we no longer need the original image, it is literally
		//of no use to us.
		SDL_FreeSurface (loadedImage);

		//optimizing it here rather than when it is blitted (drawn to surface)
		//is more efficient.  chances are you may need this image again; but now
		//since you optimize it when it is first loaded, it doesn't need to be
		//optimized again upon drawing it to the surface
	}

	//return pointer to the optimized image
	return finalImage;
}

/* Displaying Image function */
void show_Surface (int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	/*
	The SDL_BlitSurface function takes 4 parameters, the image we're going to display,
	what we're displaying it to, a rect. cropping the image (in most cases, you might 
	not want to, therefore you would put NULL) and a rect. to tell the image exactly 
	where to display itself on the given surface (ex. screen).

	SDL_BlitSurface(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect)

	"show_Surface" will take in a surface (image) to be displayed,and a surface to display
	it to just like SDL_BlitSurface.  However, just so that we won't have to constantly make
	a rect. to tell the image where exactly to display, "show_Surface" will also take in 2
	parameters (x and y positions) which will be given to a temporary rect. made inside 
	this function.

	Now we won't have to consistently make new rect. every time we want to display a (surface).
	*/

	//Temporary rectangle used to tell function where to display source surface on screen
	SDL_Rect offset;

	//Taking in the positions given to the function
	offset.x = x;
	offset.y = y;

	//Displaying the surface
	SDL_BlitSurface( source, NULL, destination, &offset);
}