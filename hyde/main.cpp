#include <SDL.h>

int main( int argc, char *argv[] ) //sdl needs exact line to find and replace main function
{
	SDL_Surface *screen;  //declare surface

	SDL_Init(SDL_INIT_EVERYTHING); //start

	screen = SDL_SetVideoMode(1600, 800, 32, SDL_SWSURFACE); //actually creates windows
	SDL_Delay(3200); // timer 3.2 seconds
	SDL_FreeSurface(screen); //memory mgmt - gets rid of surface

	SDL_Quit(); //end
	return 0;
}