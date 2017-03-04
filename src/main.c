// Standard C headers
#include <stdlib.h>
#include <stdio.h>

// Third-party library headers
#include <SDL.h>
#include <chipmunk.h>

// Custom headers
#include "boolean.h"

// functions from startApp() - endApp() must be defined before main() or the program will receive a "identifier not found" error

// will start the application by initializing everything this game depends on to run
bool startApp()
{
	// switches SDL on, if it doesn't work, return false
	if (SDL_Init(SDL_INIT_EVERYTHING))	
		return false;
	
	// if it does work, the program will skip the "return false" line and return true instead
	return true;
}

// checks when the user inputs anything
void input()
{

}

// updates everything that's going on in the game, usually according to user input, which is why it's called after input
void update()
{

}

// draws/renders all the changes according to input and update
void draw()
{

}

//
void endApp()
{
	// switches SDL off
	SDL_Quit();
}

// the program begins HERE
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