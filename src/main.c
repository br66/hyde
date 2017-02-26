#include <stdlib.h>
#include <stdio.h>

// these functions must be defined before main or I get identifier not found

bool startApp()
{
	return true;
}

void input()
{

}

void update()
{

}

void draw()
{

}

void endApp()
{

}

int main(int argc, char *argv[])
{
	// create boolean for determining when the app should stop running
	bool done = false;

	// If launching the app is successful,
	if (startApp())
	{
		// print success message
		printf("Project2017 SDL ver2  Chipmunk ver???");

		do
		{
			input();
			update();
			draw();
		} 
		while (!done);
	}

	// game will only run while done is still false, if ever true, it reaches here
	endApp();
	exit(0);

	// application will end
	return 0;
}