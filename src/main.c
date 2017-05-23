/**********************************************************************************************//**
 * @file	main.c
 * @author	br66
 * @date	5/8/17
 * @brief	main is for utilities
 *			will describe 
 **************************************************************************************************/

// Standard C headers
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

// Third-party library headers
#include <SDL.h>
#include <chipmunk.h>

// Custom headers
#include "main.h"
#include "boolean.h"
#include "entity.h"

// Main/Util
static SDL_Window* window;

// Time ------------------------
Uint32 delta = 0; // Unsigned 32-bit integer: non-negative number from 0 to 4,294,967,295 (2^32 - 1)
Uint32 start = 0; // timestamp of when SDL launched
static Uint32 currentTime = 0; // static variable: can only be used within this .c file

// Input ------------------------
SDL_Event event; // structure for input event information

// Functions ------------------------
// functions from startApp() - endApp() must be defined before main() or the program will receive a "identifier not found" error
// will start the application by initializing everything this game depends on to run

/*************************************************************************************************/
/**
* @fn	bool startApp()
*
* @brief	Runs appropiate instructions to start the application.
* @return	true if everything in this function runs properly, false if anything fails
* @author	br66
* @date		5/8/2017
*/
/*************************************************************************************************/
bool startApp()
{
	// Start/launch SDL ------------------------
	if (SDL_Init(SDL_INIT_EVERYTHING)) return false; 
	// if it doesn't work, return false

	// Open window ------------------------
	window = SDL_CreateWindow(
		"2017",								// window title
		SDL_WINDOWPOS_UNDEFINED,			// initial x position
		SDL_WINDOWPOS_UNDEFINED,			// initial y position
		640,								// width, in pixels
		480,								// height, in pixels
		SDL_WINDOW_OPENGL					// flags, mess with SDL_WINDOW_ALLOW_HIGHDPI at some point
	);

	if (!window) return false;
	
	// Save the timestamp of when SDL finished launching ------------------------
	start = SDL_GetTicks(); 
	// start tracking milliseconds since SDL started and save the number, potential use for game mechanics
	// SDL_GetTicks() also gives the amount of milliseconds that have passed up until the point of the frame we are currently at

	// Create place in computer memory to store entities ------------------------
	EntityMInit(); 
	// change to if statement?

	// Create one entity ------------------------
	struct Entity* ent = NewEntity(); // Creation of new entity
	strcpy(ent->m_name, "My first entity"); // Giving the new entity a name

	return true; // if everything above runs, the program will skip the "return false" line and return true instead
}


void input() // checks when the user inputs anything
{
	//check if quitted to turn done to true
}

void update() // updates everything that's going on in the game, usually according to user input, which is why it's called after input
{
	// DeltaTime();
	// delta time - change in time; difference between when SDL_GetTicks was last called and now
	// the more content put into the game, the less likely the game will be able to complete one
	// frame before the end of one millisecond; it will vary from time to time.  in order to keep up 
	// with time, we must calculate the difference between my last completed frame and the current frame

	delta = SDL_GetTicks() - currentTime; // delta time = difference between the # of milliseconds I get from SDL_GetTicks() NOW and the num. I got when I last called it
	
	// delta = SDL_GetTicks() - Time();
	printf("%" PRIu32 "\n", delta); // testing new delta time, previously only ran during certain game modes

	currentTime = SDL_GetTicks(); // store the "# of millseconds I get from SDL_GetTicks() NOW" in currentTime, overwriting the previous time, for when I reached update again
}

void draw() // draws/renders all the changes from update
{
	// draw all objects sprite components
}

void endApp() // shut down, deallocate everything, free memory for other Apps running on computer
{
	EntityMDel(); // clear all entities from memory

	SDL_Quit(); // switches SDL off

	exit(0); // exit, unknown parameter
}

int main(int argc, char *argv[]) // <<<<< the program starts HERE
{
	bool done = false; // create boolean for determining when the app should stop running
	// at some point this boolean will be turned true, most likely by input from the player

	if (startApp()) // If launching the app is successful,
	{	
		// SDL2 is "dynamically linked" to this project.  This means that
		// it is linked (combined?) with the rest of my project when the
		// .exe is running.  The version of SDL that I'm compiling may be
		// different than the one that is linked.

		SDL_version compiledVersion;
		SDL_VERSION(&compiledVersion);

		printf("Project2017 SDL ver%d.%d.%d  Chipmunk ver%s", compiledVersion.major, compiledVersion.minor, compiledVersion.patch, cpVersionString); // print success message
		
		do  // do run the game while the game is told it's not done running
		{
			input(); // takes the input
			update(); // updates everything based on changes from input, etc.
			draw(); // draws all the results from input(), update(), etc.
		} while (!done); // (!done) means NOT done
	}
	
	endApp(); // game will only run while done is still false, if ever true, it reaches here

	return 0; // application will end
}