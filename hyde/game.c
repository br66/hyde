#include <stdlib.h>
#include <SDL.h> //not subject to change
#include <SDL_image.h>
#include "graphics.h" //may change
#include <string.h>

#include <objectTest.h>

/**********************************
EXTERNALS
**********************************/
extern SDL_Surface *screen = NULL;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
//extern SDL_Rect Camera;
extern SDL_Surface *dot = NULL;
/*********************************/

/*********************************
FOR EVENTS LIKE KEYSTATES (PRESS AND RELEASE)
*********************************/
SDL_Event event;

/*********************************
FOR INITALIZING ALL TEH GRAPHIX
*********************************/
void Init_All(); //this function exists

/*********************************
FOR OBJECTS
*********************************/
const int OBJTEST_WIDTH = 20;
const int OBJTEST_HEIGHT = 20;

/*********************************
CLASSES FOR 
*********************************/
/*class objTest
{
private:
	int x, y; //position
	int xVel, yVel; //speeeeeeeeeeeeeeeeeeeeeeeeeed

public:
	objTest();
}*/



int main(int argc, char *argv[]) 
{	
/***********************************************************************************************************************/
//Start()												lol im unity were im supposed to b c							/
/***********************************************************************************************************************/
	SDL_Surface *bg;

	int done;
	int keyn;

	Uint8 *keys;

	Init_All();

	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE); 

	bg = SDL_LoadBMP("actionstashhd.bmp");

	if(bg != NULL)
	{
		SDL_BlitSurface(bg,NULL,buffer,NULL);
	}
	
	done = 0;
/***********************************************************************************************************************/

/***********************************************************************************************************************/
//FixedUpdate()																											/
/***********************************************************************************************************************/
	do
	{
		ResetBuffer();
		//DrawMouse();
		NextFrame();
		SDL_PumpEvents();

		keys = SDL_GetKeyState(&keyn);

		if(keys[SDLK_UP])
		if(keys[SDLK_ESCAPE])done = 1; //if i press escape, game over
	}
	while(!done); SDL_FreeSurface(screen); exit(0);
	return 0;
}
/***********************************************************************************************************************/

void CleanUpAll()
{
  CloseSprites();
  /*any other cleanup functions can be added here*/ 
}

void Init_All()
{
  Init_Graphics();

  //InitMouse();
  atexit(CleanUpAll); //when the program exits
}