#include "include.h"

void fire_Bomb (entity_t *ent)
{
	entity_t *bomb;

	bomb = initEnt();

	bomb->owner = ent;

	bomb->x = ent->x;
	bomb->y = ent->y;

	SET_FLAG(bomb->flags, ENT_SHOW);

	bomb->bBox.w = 20;
	bomb->bBox.h = 20;

	bomb->sprite = load("graphic/enemy/projectile/bomb.png", 32, 32); //#sprite
	bomb->show = showEnt;
}

void fire_Projectile (entity_t *shooter)
{
	entity_t *projectile; /* create projectile */

	projectile = initEnt(); /* put into memory */

	projectile->owner = shooter; /* owner of this projectile is whoever shot it (whoever called this function)*/
	sprintf(projectile->classname, "enemy");

	projectile->x = shooter->x;
	projectile->y = shooter->y;

	SET_FLAG(projectile->flags, ENT_SHOW);
	SET_FLAG(projectile->flags, ENT_THINK);

	projectile->bBox.h = 64;
	projectile->bBox.w = 64;

	projectile->sprite = load("graphic/enemy/projectile/projectile.png", 32, 32);; //#sprite
	projectile->show = showEnt;

	projectile->think = projThink;
	projectile->nextThink = getCurrentTime() + 100;
}