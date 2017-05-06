// .c

// Standard C headers
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

// Third-party library headers
#include <SDL.h>
#include <chipmunk.h>

// Custom headers 
#include "time.h"
#include "boolean.h"
#include "entity.h"

// Game game;

// Uint32 - Unsigned 32-bit integer: non-negative number from 0 to 4,294,967,295 (2^32 - 1)
Uint32 delta = 0;
Uint32 start = 0;

SDL_Event event;

// static variable: can only be used within this .c file
static Uint32 currentTime = 0;

// functions from startApp() - endApp() must be defined before main() or the program will receive a "identifier not found" error

// will start the application by initializing everything this game depends on to run
bool startApp()
{
	// launch SDL, if it doesn't work, return false
	if (SDL_Init(SDL_INIT_EVERYTHING))	
		return false;
	
	// start tracking milliseconds since SDL started and save the number, potential use for game mechanics
	start = SDL_GetTicks();
	// SDL_GetTicks() also gives the amount of milliseconds that have passed up until the point of the frame we are currently at

	// specifics, change to if statement?
	EntityMInit();

	struct Entity* ent = NewEntity();
	strcpy(ent->m_name, "My first entity");

	// if everything above runs, the program will skip the "return false" line and return true instead
	return true;
}

// checks when the user inputs anything
void input()
{
	//check if quitted to turn done to true;
}

// updates everything that's going on in the game, usually according to user input, which is why it's called after input
void update()
{
	// DeltaTime();
	// delta time - change in time; difference between when SDL_GetTicks was last called and now
	// the more content put into the game, the less likely the game will be able to complete one
	// frame before the end of one millisecond; it will vary from time to time.  in order to keep up 
	// with time, we must calculate the difference between my last completed frame and the current frame

	// delta time = difference between the # of milliseconds I get from SDL_GetTicks() NOW and the num. I got when I last called it
	delta = SDL_GetTicks() - currentTime;
	
	// testing new delta time, previously only ran during certain game modes
	// delta = SDL_GetTicks() - Time();
	printf("%" PRIu32 "\n", delta);

	// store the "# of millseconds I get from SDL_GetTicks() NOW" in currentTime, overwriting the previous time, for when I reached update again
	currentTime = SDL_GetTicks();
}

// draws/renders all the changes from update
void draw()
{
	// draw all objects sprite components
}

// shut down, deallocate everything, free memory for other Apps running on computer
void endApp()
{
	// clear all entities from memory
	EntityMDel();

	// switches SDL off
	SDL_Quit();

	// exit, unknown parameter
	exit(0);
}

// the program starts HERE
int main(int argc, char *argv[])
{
	// create boolean for determining when the app should stop running
	// at some point this boolean will be turned true, most likely by input from the player
	bool done = false;

	// If launching the app is successful,
	if (startApp())
	{	
		// SDL2 is "dynamically linked" to this project.  This means that
		// it is linked (combined?) with the rest of my project when the
		// .exe is running.  The version of SDL that I'm compiling may be
		// different than the one that is linked.

		SDL_version compiledVersion;
		SDL_VERSION(&compiledVersion);

		// print success message
		printf("Project2017 SDL ver%d.%d.%d  Chipmunk ver%s", compiledVersion.major, compiledVersion.minor, compiledVersion.patch, cpVersionString);
		
		// do run the game while the game is told it's not done running
		do
		{
			input(); // takes the input
			update(); // updates everything based on changes from input, etc.
			draw(); // draws all the results from input(), update(), etc.
		} while (!done); // (!done) means NOT done
	}

	// game will only run while done is still false, if ever true, it reaches here
	endApp();

	// application will end
	return 0;
}