#include <SDL.h>

int main( int argc, char *argv[] )
{
	SDL_Surface *screen;

	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(1600, 800, 32, SDL_SWSURFACE);
	SDL_Delay(3200);
	SDL_FreeSurface(screen);

	SDL_Quit();
	return 0;
}