#include <SDL.h>
#include <SDL_ttf.h>
#include "graphic.h"
#include "gfunc.h"


void drawText (char * text, SDL_Surface * screen, int x, int y, Uint32 color)
{
	SDL_Surface * fontSurface = NULL;

	SDL_Rect dst;

	//fontSurface = TTF_RenderText_Solid(getFont(), text, timeColor); 
	
	dst.x = x;
	dst.y = y;

	SDL_BlitSurface (fontSurface, NULL, getScreen(), &dst);
	SDL_FreeSurface (fontSurface);
	
}

void drawTextBox (char * title, char * text, int length)
{
	// rectangle for window
	SDL_Rect rect;

	//set up rectangle proportional to the maximum length (int length)
	rect.x = (getScreen()->w >> 1) - (length * 4);
	rect.y = (getScreen()->h >> 1);
	rect.w = (length * 8);
	rect.h = 60;

	//fill the rectangle
	SDL_FillRect(getScreen(), &rect, SDL_MapRGB(getScreen()->format,255,128,64));
	
	//draw the title
	drawText (title, getScreen(), rect.x, rect.y, SDL_MapRGB(getScreen()->format,0,128,0));

	//draw text from string, check if text is string for drawing
	if(strlen(text) > 0)
		drawText(text, getScreen(), rect.x, rect.y, SDL_MapRGB(getScreen()->format,128,128,0));
}