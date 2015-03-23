#include "include.h"

void fire_Bomb (entity_t *ent)
{
	entity_t *bomb;

	bomb = Init_Ent();

	bomb->owner = ent;

	bomb->x = ent->x;
	bomb->y = ent->y;

	SET_FLAG(bomb->flags, ENTFLAG_SHOW);

	//bomb->bBox.x = bomb->x;
	//bomb->bBox.y = bomb->y;
	//bomb->bBox.w = 20;
	//bomb->bBox.h = 20;
	bomb->sprite = bombSprite;
	bomb->show = show_Enemy;
}

void fire_Projectile (entity_t *shooter)
{
	entity_t *projectile; /* create projectile */

	projectile = Init_Ent(); /* put into memory */

	projectile->owner = shooter; /* owner of this projectile is whoever shot it (whoever called this function) */
	sprintf(projectile->classname, "enemy");

	projectile->x = shooter->x;
	projectile->y = shooter->y;

	SET_FLAG(projectile->flags, ENTFLAG_SHOW);
	SET_FLAG(projectile->flags, ENTFLAG_THINK);

	//projectile->bBox.x = projectile->x;
	//projectile->bBox.y = projectile->y;
	//projectile->bBox.h = 64;
	//projectile->bBox.w = 64;

	projectile->sprite = bombSprite;
	projectile->show = show_Enemy;

	projectile->think = projThink;
	projectile->nextThink = currentTime + 100;
}