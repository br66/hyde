#include	"include.h"

SDL_Surface *screen = NULL;	
SDL_Surface *bgSprite = NULL;
SDL_Surface *bgSprite2 = NULL;
SDL_Surface *platformSprite1 = NULL;
SDL_Surface *platformSpriteA1 = NULL;
SDL_Surface *platformSprite2 = NULL;
SDL_Surface *platformSpriteA2 = NULL;

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

entity_t *enemy1 = NULL;
entity_t *enemy2 = NULL;
entity_t *enemy3 = NULL;

entity_t *boss = NULL;

entity_t *wall = NULL;

entity_t *player = NULL;

level_t *stage1 = NULL;
level_t *stage2 = NULL;