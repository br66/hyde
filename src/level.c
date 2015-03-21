#include "include.h"

/* level functions */
void show_LevelOne()
{
	show_Surface (0, 0, stage1->backgrounds[0], screen, &camera);
	//show_Surface (0 - (float)camera.x, 410 - (float)camera.y, stage1->lvlEntities[0]->sprite, screen, NULL);
		
	//other level 1 assets
	if (enemy1)
	{
		SET_FLAG(enemy1->flags, ENTFLAG_SHOW);
		SET_FLAG(enemy1->flags, ENTFLAG_THINK);
	}
	if (enemy2)
	{
		SET_FLAG(enemy2->flags, ENTFLAG_SHOW);
		SET_FLAG(enemy2->flags, ENTFLAG_THINK);
	}
	if (enemy3)
	{
		SET_FLAG(enemy3->flags, ENTFLAG_SHOW);
		SET_FLAG(enemy3->flags, ENTFLAG_THINK);
	}

	if (boss)
	{
		REMOVE_FLAG(boss->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(boss->flags, ENTFLAG_THINK);
	}

	if(wall)
	{
		SET_FLAG(wall->flags, ENTFLAG_THINK);
		SET_FLAG(wall->flags, ENT_SOLID);
	}
	
	if(platform1)
	{
		SET_FLAG(platform1->flags, ENTFLAG_SHOW);
		SET_FLAG(platform1->flags, ENT_SOLID);
	}
	if(platform2)
	{
		SET_FLAG(platform2->flags, ENTFLAG_SHOW);
		SET_FLAG(platform2->flags, ENT_SOLID);
	}
	if(platform3)
	{
		SET_FLAG(platform3->flags, ENTFLAG_SHOW);
		SET_FLAG(platform3->flags, ENT_SOLID);
	}
	if(platform4)
	{
		SET_FLAG(platform4->flags, ENTFLAG_SHOW);
		SET_FLAG(platform4->flags, ENT_SOLID);
	}

	if(platformA1)
	{
		REMOVE_FLAG(platformA1->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(platformA1->flags, ENT_SOLID);
	}
	if(platformA2)
	{
		REMOVE_FLAG(platformA2->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(platformA2->flags, ENT_SOLID);
	}
	if(platformA3)
	{
		REMOVE_FLAG(platformA3->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(platformA3->flags, ENT_SOLID);
	}
	if(platformA4)
	{
		REMOVE_FLAG(platformA4->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(platformA4->flags, ENT_SOLID);
	}
}

void show_LevelTwo()
{
	show_Surface (0, 0, stage2->backgrounds[0], screen, &camera);
	//show_Surface (0 - (float)camera.x, 410 - (float)camera.y, stage2->surfaces[1], screen, NULL);

	if (enemy1)
	{
		REMOVE_FLAG(enemy1->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(enemy1->flags, ENTFLAG_THINK);
	}
	if (enemy2)
	{
		REMOVE_FLAG(enemy2->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(enemy2->flags, ENTFLAG_THINK);
	}
	if (enemy3)
	{
		REMOVE_FLAG(enemy3->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(enemy3->flags, ENTFLAG_THINK);
	}

	if (boss)
	{
		SET_FLAG(boss->flags, ENTFLAG_SHOW);
		SET_FLAG(boss->flags, ENTFLAG_THINK);
	}
	if(platform1)
	{
		REMOVE_FLAG(platform1->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(platform1->flags, ENT_SOLID);
	}
	if(platform2)
	{
		REMOVE_FLAG(platform2->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(platform2->flags, ENT_SOLID);
	}
	if(platform3)
	{
		REMOVE_FLAG(platform3->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(platform3->flags, ENT_SOLID);
	}
	if(platform4)
	{
		REMOVE_FLAG(platform4->flags, ENTFLAG_SHOW);
		REMOVE_FLAG(platform4->flags, ENT_SOLID);
	}
	if(platformA1)
	{
		SET_FLAG(platformA1->flags, ENTFLAG_SHOW);
		SET_FLAG(platformA1->flags, ENT_SOLID);
	}
	if(platformA2)
	{
		SET_FLAG(platformA2->flags, ENTFLAG_SHOW);
		SET_FLAG(platformA2->flags, ENT_SOLID);
	}
	if(platformA3)
	{
		SET_FLAG(platformA3->flags, ENTFLAG_SHOW);
		SET_FLAG(platformA3->flags, ENT_SOLID);
	}
	if(platformA4)
	{
		SET_FLAG(platformA4->flags, ENTFLAG_SHOW);
		SET_FLAG(platformA4->flags, ENT_SOLID);
	}
}