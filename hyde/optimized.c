#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>

//kehoe
#include "graphics.h"

//size of the window, constant, will not change
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//bits per pixel
const int SCREEN_BPP = 16;

//three images will be used
extern SDL_Rect Camera;
extern SDL_Surface *buffer = NULL;
extern SDL_Surface *screen = NULL;
//set pointers to null, if not pointing to anything

//void Iam_A_Thing();

Uint8 *keystates = SDL_GetKeyState( NULL ); // ta taik inn teh kees

SDL_Surface *load_image ( std::string filename )
{
	//temporarily storing the image...
	SDL_Surface* loadedImage = NULL;

	//create a verison of the image optimized for project
	SDL_Surface* optimizedImage = NULL;
}