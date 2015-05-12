#include "include.h"

extern game_t Game;

void newSpawnEntity (const char * name, float x, float y, const char * flag)
{
	entity_t * spawn = Init_Ent();

	if (strcmp(name, "kid") == 0)
	{
		strcpy(spawn->classname, "kid");
		strcpy(spawn->classType, "enemy");
		spawn->sprite = load("graphic/enemy/kid.png", 16, 23);

		spawn->bBox.w = 16;
		spawn->bBox.h = 23;

		spawn->think = betaThink;
		spawn->nextThink = getCurrentTime() + 2000;
	}

	SET_FLAG(spawn->flags, ENT_SOLID);
}

void spawnEntity(const char * name, float x, float y, const char * flag)
{
	if (strcmp(name, "kid") == 0)
	{
		entity_t * kid = Init_Ent();

		strcpy(kid->classname, "kid");
		strcpy(kid->classType, "enemy");
		kid->sprite = load("graphic/enemy/kid.png", 16, 23);
		kid->x = x;
		kid->y = y;
		kid->bBox.w = 16;
		kid->bBox.h = 23;
		kid->show = show_Ent;
		kid->think = betaThink;
		kid->nextThink = getCurrentTime() + 2000;

		if (strcmp(flag, "jekyll") == 0 /*&& Game.levelState == JEKYLL_MODE*/)
		{
			strcpy(kid->mode, "jekyll");
			SET_FLAG(kid->flags, ENT_FJEKYL);
		}

		if (strcmp(flag, "hyde") == 0 /*&& Game.levelState == HYDE_MODE*/)
			SET_FLAG(kid->flags, ENT_FHYDE);

		SET_FLAG(kid->flags, ENT_SOLID);
	}

	if (strcmp(name, "platform 1") == 0)
	{
		cpShape * edge = NULL;

		entity_t * platform1 = Init_Ent();
		strcpy(platform1->classname, "platform 1");
		platform1->sprite = load("graphic/level/lvldesign/plvl_1.png", 62, 24);
		platform1->x = x;
		platform1->y = y;
		platform1->bBox.w = 62;
		platform1->bBox.h = 24;
		platform1->show = show_Ent;

		SET_FLAG(platform1->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
		{
			strcpy(platform1->mode, "jekyll");
			SET_FLAG(platform1->flags, ENT_FJEKYL);
		}

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(platform1->flags, ENT_FHYDE);

		if (Game.gameState != GSTATE_LEVELEDIT)
		{
			edge = cpBoxShapeNew(cpSpaceGetStaticBody(getSpace()), 62, 40);
			edge->e = 0;
			edge->u = 0;
			cpBodySetPos(cpSpaceGetStaticBody(getSpace()), cpv(x, y));
			cpShapeSetCollisionType(edge, 1);
			cpShapeSetLayers(edge,CP_ALL_LAYERS);
			cpShapeSetUserData(edge, (const cpDataPointer)platform1);
			cpSpaceAddStaticShape(getSpace(), edge);
		}
	}

	if (strcmp(name, "bomber") == 0)
	{
		entity_t * bomber = Init_Ent ();

		strcpy(bomber->classname, "bomber");
		strcpy(bomber->classType, "enemy");

		bomber->sprite = load("graphic/enemy/bomber.png", 16, 33);
		bomber->x = x;
		bomber->y = y;
		bomber->bBox.w = 16;
		bomber->bBox.h = 33;
		bomber->show = show_Ent;
		bomber->think = alphaThink;

		//SET_FLAG(bomber->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(bomber->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(bomber->flags, ENT_FHYDE);
	}

	if (strcmp(name, "bird") == 0)
	{
		entity_t * bird = Init_Ent ();

		strcpy(bird->classname, "bird");
		strcpy(bird->classType, "enemy");

		bird->sprite = load("graphic/enemy/bird.png", 15, 13);
		bird->x = x;
		bird->y = y;
		bird->bBox.w = 15;
		bird->bBox.h = 13;
		bird->show = show_Ent;
		bird->think = gammaThink;

		SET_FLAG(bird->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(bird->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(bird->flags, ENT_FHYDE);
	}

	if (strcmp(name, "platform 2") == 0)
	{
		cpShape * edge = NULL;

		entity_t * platform2 = Init_Ent ();

		strcpy(platform2->classname, "platform 2");

		platform2->sprite = load("graphic/level/lvldesign/plvl1_2.png", 271, 56);
		platform2->x = x;
		platform2->y = y;
		platform2->bBox.w = 271;
		platform2->bBox.h = 56;
		platform2->show = show_Ent;

		SET_FLAG(platform2->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(platform2->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(platform2->flags, ENT_FHYDE);

		/*edge = cpBoxShapeNew(cpSpaceGetStaticBody(getSpace()), 100, 60);
		edge->e = 0;
		edge->u = 0;
		cpBodySetPos(cpSpaceGetStaticBody(getSpace()), cpv(x, y));
		cpShapeSetCollisionType(edge, 1);
		cpShapeSetLayers(edge,CP_ALL_LAYERS);
		cpShapeSetUserData(edge, (const cpDataPointer)platform2);
		cpSpaceAddStaticShape(getSpace(), edge);*/

	}

	if (strcmp(name, "platform 3") == 0)
	{
		cpShape * edge = NULL;

		entity_t * platform3 = Init_Ent ();

		strcpy(platform3->classname, "platform 3");

		platform3->sprite = load("graphic/level/lvldesign/plvl01_4.png", 62, 24);
		platform3->x = x;
		platform3->y = y;
		platform3->bBox.w = 62;
		platform3->bBox.h = 24;
		platform3->show = show_Ent;

		SET_FLAG(platform3->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(platform3->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(platform3->flags, ENT_FHYDE);

		/*edge = cpBoxShapeNew(cpSpaceGetStaticBody(getSpace()), 62, 40);
		edge->e = 0;
		edge->u = 0;
		cpBodySetPos(cpSpaceGetStaticBody(getSpace()), cpv(x, y));
		cpShapeSetCollisionType(edge, 1);
		cpShapeSetLayers(edge,CP_ALL_LAYERS);
		cpShapeSetUserData(edge, (const cpDataPointer)platform3);
		cpSpaceAddStaticShape(getSpace(), edge);*/

	}

	if (strcmp(name, "platform 4") == 0)
	{
		cpShape * edge = NULL;

		entity_t * platform4 = Init_Ent ();

		strcpy(platform4->classname, "platform 4");

		platform4->sprite = load("graphic/level/lvldesign/plvlx1_3.png", 271, 56);
		platform4->x = x;
		platform4->y = y;
		platform4->bBox.w = 271;
		platform4->bBox.h = 56;
		platform4->show = show_Ent;

		SET_FLAG(platform4->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(platform4->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(platform4->flags, ENT_FHYDE);

		
		edge = cpBoxShapeNew(cpSpaceGetStaticBody(getSpace()), 271, 60);
		edge->e = 0;
		edge->u = 0;
		cpBodySetPos(cpSpaceGetStaticBody(getSpace()), cpv(x+129, y));
		cpShapeSetCollisionType(edge, 1);
		cpShapeSetLayers(edge,CP_ALL_LAYERS);
		cpShapeSetUserData(edge, (const cpDataPointer)platform4);
		cpSpaceAddStaticShape(getSpace(), edge);

	}

	if (strcmp(name, "building 1") == 0)
	{
		entity_t * building1 = Init_Ent ();

		strcpy(building1->classname, "building 1");

		building1->sprite = load("graphic/level/lvldesign/build1_1.png", 64, 111);
		building1->x = x;
		building1->y = y;
		building1->bBox.w = 64;
		building1->bBox.h = 111;
		building1->show = show_Ent;

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(building1->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(building1->flags, ENT_FHYDE);
	}

	if (strcmp(name, "building 2") == 0)
	{
		entity_t * building2 = Init_Ent ();

		strcpy(building2->classname, "building 2");

		building2->sprite = load("graphic/level/lvldesign/build2_1.png", 64, 111);
		building2->x = x;
		building2->y = y;
		building2->bBox.w = 127;
		building2->bBox.h = 159;
		building2->show = show_Ent;

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(building2->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(building2->flags, ENT_FHYDE);
	}

	if (strcmp(name, "light 1") == 0)
	{
		entity_t * light1 = Init_Ent ();

		strcpy(light1->classname, "light 1");

		light1->sprite = load("graphic/level/lvldesign/light1_1.png", 64, 111);
		light1->x = x;
		light1->y = y;
		light1->bBox.w = 127;
		light1->bBox.h = 159;
		light1->show = show_Ent;

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(light1->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(light1->flags, ENT_FHYDE);
	}

	if (strcmp(name, "kid spawner") == 0)
	{
		entity_t * spawnerKid = Init_Ent ();

		strcpy(spawnerKid->classname, "kid spawner");

		spawnerKid->x = x;
		spawnerKid->y = y;
		spawnerKid->think = spawnThink;
		spawnerKid->nextThink = getCurrentTime() + 70;

		SET_FLAG(spawnerKid->flags, ENT_SHOW); //might change this
	}
}