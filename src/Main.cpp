/**********************************************************************************************//**
 * @file	main.cpp
 * @author	br66
 * @date	5/29/17
 * @brief	main.cpp - where the game starts
 **************************************************************************************************/

// Standard library headers
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

// Third-party library headers
#include <SDL.h>
#include <chipmunk.h>

// Custom headers
#include "main.hpp"
#include "boolean.h"

// For test and debug
#include "Entity.hpp"

 /*************************************************************************************************/
 /**
 * @fn	int main(int argc, char *argv[])
 *
 * @brief	Entry point of app.  When a user want to use this app, this function is called.
 * @return	0 when the function ends (meaning the game needs to be closed)
 * @author	br66
 * @date	5/29/2017
 */
 /*************************************************************************************************/
int main(int argc, char *argv[])
{
	bool done = false; // created for determining when the app should exit
					   // if ever turned true, it would most likely be through player input

	Entity test;
	test.SetOwner(&test);
	
	// "It is unnecessary to delete the object."
	//delete(test);

	/* 
		what i need

		now has past and must be set to then (time)
		get now time
		get the difference between now and then - the delta

		if the delta is less than the delay
			delay the frame

		the fps: 1000/max(ticks - the then time, 0.001)
	*/
	exit(0);
	return 0; // app will remove itself from memory and close

}