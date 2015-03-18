#include	<SDL.h>
#include	<SDL_ttf.h>
#include	<SDL_mixer.h>
#include	"graphics.h"

SDL_Surface *screen = NULL;	
SDL_Surface *bgSprite = NULL;
SDL_Surface *bgSprite2 = NULL;

SDL_Surface *message = NULL;

SDL_Surface *seconds = NULL;

SDL_Rect health;
SDL_Rect anger;

SDL_Surface *bombSprite = NULL;
SDL_Surface *bossSprite = NULL;

TTF_Font *font = NULL;

SDL_Color textColor = { 255, 255, 255 };

Mix_Music *music= NULL;

Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;

SDL_Surface *dot = NULL;

int frameCount;

SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

SDL_Event event;

Uint8 *keystates;
Uint32 currentTime = 0;
Uint32 delta = 0;