/* Things in this file are gradually being
moved and replaced. This file will be removed 
soon, but the remaining variables will be 
replaced by yaml. */

#include	"include.h"

//THE FOLLOWING CANNOT BE MOVED UNITL YAML IS IMPLEMENTED

SDL_Surface *platformSprite1 = NULL;
SDL_Surface *platformSpriteA1 = NULL;
SDL_Surface *platformSprite2 = NULL;
SDL_Surface *platformSpriteA2 = NULL;

SDL_Surface *bombSprite = NULL;
SDL_Surface *bossSprite = NULL;

SDL_Surface *plyrSprite = NULL;

//int frameCount;

SDL_Event event;

entity_t *enemy1 = NULL;
entity_t *enemy2 = NULL;
entity_t *enemy3 = NULL;

entity_t *lvlTrigger = NULL;

entity_t *boss = NULL;

entity_t *wall = NULL;

level_t *stage1 = NULL;
level_t *stage2 = NULL;