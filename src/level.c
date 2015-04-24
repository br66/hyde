//Nothing changed here
#include "include.h"

/* lvl/stage 1 specific entities */
entity_t *platform1;
entity_t *platform2;
entity_t *platform3;
entity_t *platform4;

extern entity_t *lvlTrigger;

extern entity_t *enemy1;
extern entity_t *enemy2;
extern entity_t *enemy3;

extern entity_t *boss;

/* lvl/stage 2 specific entities */
entity_t *platformA1;
entity_t *platformA2;
entity_t *platformA3;
entity_t *platformA4;


//-----
extern level_t *stage1;
extern level_t *stage2;

extern entity_t *wall;

/* level functions */
void show_LevelOne()
{
	show_Surface (0, 0, stage1->backgrounds[0], getScreen(), addrCamera());
		
	//other level 1 assets
	if (enemy1)
	{
		SET_FLAG(enemy1->flags, ENT_SHOW);
		SET_FLAG(enemy1->flags, ENT_THINK);
		SET_FLAG(enemy1->flags, ENT_SOLID);
	}
	if (enemy2)
	{
		SET_FLAG(enemy2->flags, ENT_SHOW);
		SET_FLAG(enemy2->flags, ENT_THINK);
	}
	if (enemy3)
	{
		SET_FLAG(enemy3->flags, ENT_SHOW);
		SET_FLAG(enemy3->flags, ENT_THINK);
	}

	if (boss)
	{
		REMOVE_FLAG(boss->flags, ENT_SHOW);
		REMOVE_FLAG(boss->flags, ENT_THINK);
		//REMOVE_FLAG(boss->flags, ENT_SOLID);
	}

	if(wall)
	{
		SET_FLAG(wall->flags, ENT_SOLID);
	}
	
	if(platform1)
	{
		SET_FLAG(platform1->flags, ENT_SHOW);
		SET_FLAG(platform1->flags, ENT_SOLID);
	}
	if(platform2)
	{
		SET_FLAG(platform2->flags, ENT_SHOW);
		SET_FLAG(platform2->flags, ENT_SOLID);
	}
	if(platform3)
	{
		SET_FLAG(platform3->flags, ENT_SHOW);
		SET_FLAG(platform3->flags, ENT_SOLID);
	}
	if(platform4)
	{
		SET_FLAG(platform4->flags, ENT_SHOW);
		SET_FLAG(platform4->flags, ENT_SOLID);
	}

	if(platformA1)
	{
		REMOVE_FLAG(platformA1->flags, ENT_SHOW);
		REMOVE_FLAG(platformA1->flags, ENT_SOLID);
	}
	if(platformA2)
	{
		REMOVE_FLAG(platformA2->flags, ENT_SHOW);
		REMOVE_FLAG(platformA2->flags, ENT_SOLID);
	}
	if(platformA3)
	{
		REMOVE_FLAG(platformA3->flags, ENT_SHOW);
		REMOVE_FLAG(platformA3->flags, ENT_SOLID);
	}
	if(platformA4)
	{
		REMOVE_FLAG(platformA4->flags, ENT_SHOW);
		REMOVE_FLAG(platformA4->flags, ENT_SOLID);
	}
	if(lvlTrigger)
	{
		SET_FLAG(lvlTrigger->flags, ENT_SOLID);
		SET_FLAG(lvlTrigger->flags, ENT_SHOW);
	}

}

void show_LevelTwo()
{
	show_Surface (0, 0, stage2->backgrounds[0], getScreen(), addrCamera());

	if (enemy1)
	{
		REMOVE_FLAG(enemy1->flags, ENT_SHOW);
		REMOVE_FLAG(enemy1->flags, ENT_THINK);
		REMOVE_FLAG(enemy1->flags, ENT_SOLID);
	}
	if (enemy2)
	{
		REMOVE_FLAG(enemy2->flags, ENT_SHOW);
		REMOVE_FLAG(enemy2->flags, ENT_THINK);
	}
	if (enemy3)
	{
		REMOVE_FLAG(enemy3->flags, ENT_SHOW);
		REMOVE_FLAG(enemy3->flags, ENT_THINK);
	}

	if (boss)
	{
		SET_FLAG(boss->flags, ENT_SHOW);
		SET_FLAG(boss->flags, ENT_THINK);
		//SET_FLAG(boss->flags, ENT_SOLID);
	}
	if(platform1)
	{
		REMOVE_FLAG(platform1->flags, ENT_SHOW);
		REMOVE_FLAG(platform1->flags, ENT_SOLID);
	}
	if(platform2)
	{
		REMOVE_FLAG(platform2->flags, ENT_SHOW);
		REMOVE_FLAG(platform2->flags, ENT_SOLID);
	}
	if(platform3)
	{
		REMOVE_FLAG(platform3->flags, ENT_SHOW);
		REMOVE_FLAG(platform3->flags, ENT_SOLID);
	}
	if(platform4)
	{
		REMOVE_FLAG(platform4->flags, ENT_SHOW);
		REMOVE_FLAG(platform4->flags, ENT_SOLID);
	}
	if(platformA1)
	{
		SET_FLAG(platformA1->flags, ENT_SHOW);
		SET_FLAG(platformA1->flags, ENT_SOLID);
	}
	if(platformA2)
	{
		SET_FLAG(platformA2->flags, ENT_SHOW);
		SET_FLAG(platformA2->flags, ENT_SOLID);
	}
	if(platformA3)
	{
		SET_FLAG(platformA3->flags, ENT_SHOW);
		SET_FLAG(platformA3->flags, ENT_SOLID);
	}
	if(platformA4)
	{
		SET_FLAG(platformA4->flags, ENT_SHOW);
		SET_FLAG(platformA4->flags, ENT_SOLID);
	}
	if(lvlTrigger)
	{
		REMOVE_FLAG(lvlTrigger->flags, ENT_SHOW);
		REMOVE_FLAG(lvlTrigger->flags, ENT_SOLID);
	}
}