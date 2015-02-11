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
SDL_Event eventT;

/*********************************
FOR INITALIZING ALL TEH GRAPHIX
*********************************/
void Init_All(); //this function exists

/*********************************
FOR OBJECTS
*********************************/
//objTest_t *star;
const int OBJTEST_WIDTH = 20;
const int OBJTEST_HEIGHT = 20;

/*********************************
FUNCTIONS FOR OBJTEST
*********************************/
void handle_Input(objTest_t *self);
//void moveObject(objTest_t *self);
//void showObject(objTest_t *self);

void applySurface (int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	//clip = NULL;

	SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, NULL, destination, &offset );
}

/*void handle_Input(objTest_t *self) //shouldn't this be at the top of the file?? 
{
	//printf("handle input\n");
	if ( eventT.type == SDL_KEYDOWN ) // << not doing this line
	{
		//printf("handle input\n");
		switch( eventT.key.keysym.sym )
		{
			case SDLK_UP: self->yVel -= OBJTEST_HEIGHT / 2; break;
			case SDLK_DOWN: self->yVel += OBJTEST_HEIGHT / 2; break;
			case SDLK_LEFT: self->xVel -= OBJTEST_WIDTH / 2; break;
			case SDLK_RIGHT: self->xVel += OBJTEST_WIDTH / 2; break;
		}
	}

	else if ( eventT.type == SDL_KEYUP )
	{

		switch ( eventT.key.keysym.sym )
		{
			case SDLK_UP: self->yVel += OBJTEST_HEIGHT / 2; break;
            case SDLK_DOWN: self->yVel -= OBJTEST_HEIGHT / 2; break;
            case SDLK_LEFT: self->xVel += OBJTEST_WIDTH / 2; break;
            case SDLK_RIGHT: self->xVel -= OBJTEST_WIDTH / 2; break;
		}
	}
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

	//star->x = 0;
	//star->y = 0;
	//star->xVel = 0;
	//star->yVel = 0;

	//ZOMG JUS LIEK QUAEK TOOOOO
	//star->handleInput = handle_Input; //just because i set it, does it mean it will happen?
	//star->move = moveObject;
	//star->show = showObject;

	Init_All();

	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE); 

	bg = SDL_LoadBMP("dot.bmp");

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
		//star->handleInput(star);
		//star->move(star);
		//star->show(star);
		
		ResetBuffer();
		NextFrame();
		SDL_PumpEvents();

		//applySurface(star->x, star->y, bg, screen, NULL);
		//SDL_BlitSurface(bg,NULL,buffer,NULL);

		keys = SDL_GetKeyState(&keyn);

		//if(keys[SDLK_UP])
		//{
			//star->xVel += 2;
			//star->x += star->xVel;
			
			//printf("guhhhh");
		//}
		
		if(keys[SDLK_ESCAPE])done = 1;

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

/*void moveObject (objTest_t *self)
{
	self->x += self->xVel;

	if ( ( self->x < 0 ) || ( self->x + OBJTEST_WIDTH > 640) )
	{
		self->x -= self->xVel;
	}

	self->y += self->yVel;
	
	if ( ( self->y < 0 ) || ( self->y + OBJTEST_HEIGHT > 480 ) )
	{
		self->y -= self->yVel;
	}
}

void showObject (objTest_t *self)
{
	applySurface(self->x, self->y, dot, screen, NULL);
}*/