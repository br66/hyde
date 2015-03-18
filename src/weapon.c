#include <SDL.h>
#include "entity.h"
#include "weapon.h"
#include "graphics.h"

extern SDL_Surface *screen;
extern SDL_Surface *bombSprite;
extern Uint32 currentTime;

void fire_Bomb (entity_t *ent)
{
	entity_t *bomb;

	bomb = Init_Ent();

	bomb->owner = ent;

	bomb->x = ent->x;
	bomb->y = ent->y;
	//bomb->bBox.x = bomb->x;
	//bomb->bBox.y = bomb->y;
	//bomb->bBox.w = 20;
	//bomb->bBox.h = 20;
	bomb->sprite = bombSprite;
	bomb->show = show_Relative;
}

void fire_Projectile (entity_t *shooter)
{
	entity_t *projectile; /* create projectile */

	projectile = Init_Ent(); /* put into memory */

	projectile->owner = shooter; /* owner of this projectile is whoever shot it (whoever called this function) */

	projectile->x = shooter->x;
	projectile->y = shooter->y;
	//projectile->bBox.x = projectile->x;
	//projectile->bBox.y = projectile->y;
	//projectile->bBox.h = 64;
	//projectile->bBox.w = 64;
	projectile->sprite = bombSprite;
	projectile->show = show_Relative;

	projectile->think = projThink;
	projectile->nextThink = currentTime + 100;
}