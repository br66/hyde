#include <SDL.h>

SDL_Surface *screen;  //declare surface

void DrawFrame(SDL_Surface* s, int frameNum)
{
	SDL_Rect r;
	SDL_Rect d;

	r.w = 128;
	r.h = 128;

	r.x = frameNum%16*128; //framing horizontally (going to the next frame (right and left))
	r.y = frameNum/16*128; //framing vertically (going to the next frame (up and down))

	d.w = 128;
	d.h = 128;
	d.x = 0;
	d.y = 0;

	SDL_BlitSurface(s, &r, screen, &d);
}

int main( int argc, char *argv[] ) //sdl needs exact line to find and replace main function
{
	int i = 0;
	
	SDL_Surface* sheet; //???
	
	SDL_Init(SDL_INIT_EVERYTHING); //start

	screen = SDL_SetVideoMode(1600, 800, 32, SDL_SWSURFACE); //actually creates windows
	sheet = SDL_LoadBMP("actionstashhd.bmp");

	//resource managment - load, utilize, destroy it

	while(true)
	{
		DrawFrame(sheet, i);
		SDL_Flip(screen);	
		SDL_Delay(100); // timer .1 seconds

		i++;
		if (i >= 16)
		{
			i = 0;
		}
	}

	SDL_FreeSurface(screen); //memory mgmt - gets rid of surface

	SDL_Quit(); //end
	return 0;
}