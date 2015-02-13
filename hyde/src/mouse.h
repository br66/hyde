#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"

struct
{
	Uint32 state;
	Uint32 shown;
	Uint32 frame;
	Uint16  x, y;
}Mouse;

void DrawMouse();
void InitMouse();