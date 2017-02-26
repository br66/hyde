#include "include.h"

extern game_t Game;

void newSpawnEntity (const char * name, float x, float y, const char * flag)
{
	entity_t * spawn = initEnt();

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
		entity_t * kid = initEnt();

		strcpy(kid->classname, "kid");
		strcpy(kid->classType, "enemy");
		kid->sprite = load("graphic/enemy/kid.png", 16, 23);
		kid->x = x;
		kid->y = y;
		kid->bBox.w = 16;
		kid->bBox.h = 23;
		kid->show = showEnt;
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

		entity_t * platform1 = initEnt();
		strcpy(platform1->classname, "platform 1");
		platform1->sprite = load("graphic/level/lvldesign/plvl_1.png", 62, 24);
		platform1->x = x;
		platform1->y = y;
		platform1->bBox.w = 62;
		platform1->bBox.h = 24;
		platform1->show = showEnt;

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
			//edge = cpBoxShapeNew(cpSpaceGetStaticBody(getSpace()), 62, 35);
			//edge->e = 0;
			//edge->u = 0;
			//cpBodySetPos(cpSpaceGetStaticBody(getSpace()), cpv(x, y));
			cpShapeSetCollisionType(edge, 1);
			//cpShapeSetLayers(edge,CP_ALL_LAYERS);
			//cpShapeSetUserData(edge, (const cpDataPointer)platform1);
			//cpSpaceAddStaticShape(getSpace(), edge);
		}
	}

	if (strcmp(name, "bomber") == 0)
	{
		entity_t * bomber = initEnt ();

		strcpy(bomber->classname, "bomber");
		strcpy(bomber->classType, "enemy");

		bomber->sprite = load("graphic/enemy/bomber.png", 16, 33);
		bomber->x = x;
		bomber->y = y;
		bomber->bBox.w = 16;
		bomber->bBox.h = 33;
		bomber->show = showEnt;
		bomber->think = alphaThink;

		//SET_FLAG(bomber->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(bomber->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(bomber->flags, ENT_FHYDE);

		SET_FLAG(bomber->flags, ENT_SOLID);
	}



	if (strcmp(name, "bird") == 0)
	{
		entity_t * bird = initEnt ();

		strcpy(bird->classname, "bird");
		strcpy(bird->classType, "enemy");

		bird->sprite = load("graphic/enemy/bird.png", 15, 13);
		bird->x = x;
		bird->y = y;
		bird->bBox.w = 15;
		bird->bBox.h = 13;
		bird->show = showEnt;
		bird->think = gammaThink;

		SET_FLAG(bird->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(bird->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(bird->flags, ENT_FHYDE);
	}

	if (strcmp(name, "platform 2") == 0) //Collision doesn't work quite right
	{
		cpShape * edge = NULL;

		entity_t * platform2 = initEnt ();

		strcpy(platform2->classname, "platform 2");

		platform2->sprite = load("graphic/level/lvldesign/plvl1_2.png", 271, 56);
		platform2->x = x;
		platform2->y = y;
		platform2->bBox.w = 271;
		platform2->bBox.h = 56;
		platform2->show = showEnt;

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
		//cpShape * edge = NULL;

		entity_t * platform3 = initEnt ();

		strcpy(platform3->classname, "platform 3");

		platform3->sprite = load("graphic/level/lvldesign/plvl01_4.png", 62, 24);
		platform3->x = x;
		platform3->y = y;
		platform3->bBox.w = 62;
		platform3->bBox.h = 24;
		platform3->show = showEnt;

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
		//cpShape * edge = NULL;

		entity_t * platform4 = initEnt ();

		strcpy(platform4->classname, "platform 4");

		platform4->sprite = load("graphic/level/lvldesign/plvlx1_3.png", 271, 56);
		platform4->x = x;
		platform4->y = y;
		platform4->bBox.w = 271;
		platform4->bBox.h = 56;
		platform4->show = showEnt;

		SET_FLAG(platform4->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(platform4->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(platform4->flags, ENT_FHYDE);

		
		/*
		edge = cpBoxShapeNew(cpSpaceGetStaticBody(getSpace()), 271, 40);
		edge->e = 0;
		edge->u = 0;
		cpBodySetPos(cpSpaceGetStaticBody(getSpace()), cpv(x+129, y));
		cpShapeSetCollisionType(edge, 1);
		cpShapeSetLayers(edge,CP_ALL_LAYERS);
		cpShapeSetUserData(edge, (const cpDataPointer)platform4);
		cpSpaceAddStaticShape(getSpace(), edge);
		*/

	}

	if (strcmp(name, "building 1") == 0)
	{
		entity_t * building1 = initEnt ();

		strcpy(building1->classname, "building 1");

		building1->sprite = load("graphic/level/lvldesign/build1_1.png", 64, 111);
		building1->x = x;
		building1->y = y;
		building1->bBox.w = 64;
		building1->bBox.h = 111;
		building1->show = showEnt;

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(building1->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(building1->flags, ENT_FHYDE);
	}

	if (strcmp(name, "building 2") == 0)
	{
		entity_t * building2 = initEnt ();

		strcpy(building2->classname, "building 2");

		building2->sprite = load("graphic/level/lvldesign/build2_1.png", 64, 111);
		building2->x = x;
		building2->y = y;
		building2->bBox.w = 127;
		building2->bBox.h = 159;
		building2->show = showEnt;

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(building2->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(building2->flags, ENT_FHYDE);
	}

	if (strcmp(name, "light 1") == 0)
	{
		entity_t * light1 = initEnt ();

		strcpy(light1->classname, "light 1");

		light1->sprite = load("graphic/level/lvldesign/light1_1.png", 64, 111);
		light1->x = x;
		light1->y = y;
		light1->bBox.w = 127;
		light1->bBox.h = 159;
		light1->show = showEnt;

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(light1->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(light1->flags, ENT_FHYDE);
	}

	if(!strcmp(name, "platform 5"))
	{
		//cpShape * edge = NULL;

		entity_t * ent = initEnt();
		strcpy(ent->classname, "platform 5");
		ent->sprite = load("graphic/level/lvldesign/62414.png", 116, 16);
		ent->x = x;
		ent->y = y;
		ent->bBox.w = 116;
		ent->bBox.h = 16;
		ent->show = showEnt;

		SET_FLAG(ent->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
		{
			strcpy(ent->mode, "jekyll");
			SET_FLAG(ent->flags, ENT_FJEKYL);
		}

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(ent->flags, ENT_FHYDE);

		/*
		if (Game.gameState != GSTATE_LEVELEDIT)
		{
			edge = cpBoxShapeNew(cpSpaceGetStaticBody(getSpace()), 62, 35);
			edge->e = 0;
			edge->u = 0;
			cpBodySetPos(cpSpaceGetStaticBody(getSpace()), cpv(x, y));
			cpShapeSetCollisionType(edge, 1);
			cpShapeSetLayers(edge,CP_ALL_LAYERS);
			cpShapeSetUserData(edge, (const cpDataPointer)ent);
			cpSpaceAddStaticShape(getSpace(), edge);
		}*/
	}

	if(!strcmp(name, "platform 8"))
	{
		//cpShape * edge = NULL;

		entity_t * ent = initEnt();
		strcpy(ent->classname, "platform 8");
		ent->sprite = load("graphic/level/lvldesign/lvl2plat8.png", 116, 16);
		ent->x = x;
		ent->y = y;
		ent->bBox.w = 116;
		ent->bBox.h = 16;
		ent->show = showEnt;

		SET_FLAG(ent->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
		{
			strcpy(ent->mode, "jekyll");
			SET_FLAG(ent->flags, ENT_FJEKYL);
		}

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(ent->flags, ENT_FHYDE);

		/*
		if (Game.gameState != GSTATE_LEVELEDIT)
		{
			edge = cpBoxShapeNew(cpSpaceGetStaticBody(getSpace()), 1000, 16);
			edge->e = 0;
			edge->u = 0;
			cpBodySetPos(cpSpaceGetStaticBody(getSpace()), cpv(x, y));
			cpShapeSetCollisionType(edge, 1);
			cpShapeSetLayers(edge,CP_ALL_LAYERS);
			cpShapeSetUserData(edge, (const cpDataPointer)ent);
			cpSpaceAddStaticShape(getSpace(), edge);
		}*/
	}

	if(!strcmp(name, "platform 9"))
	{
		//cpShape * edge = NULL;

		entity_t * ent = initEnt();
		strcpy(ent->classname, "platform 9");
		ent->sprite = load("graphic/level/lvldesign/plvl5_9.png", 224, 102);
		ent->x = x;
		ent->y = y;
		ent->bBox.w = 224;
		ent->bBox.h = 102;
		ent->show = showEnt;

		SET_FLAG(ent->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
		{
			strcpy(ent->mode, "jekyll");
			SET_FLAG(ent->flags, ENT_FJEKYL);
		}

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(ent->flags, ENT_FHYDE);

		/*
		if (Game.gameState != GSTATE_LEVELEDIT)
		{
			edge = cpBoxShapeNew(cpSpaceGetStaticBody(getSpace()), 224, 98);
			edge->e = 0;
			edge->u = 0;
			cpBodySetPos(cpSpaceGetStaticBody(getSpace()), cpv(x+100, y+30));
			cpShapeSetCollisionType(edge, 1);
			cpShapeSetLayers(edge,CP_ALL_LAYERS);
			cpShapeSetUserData(edge, (const cpDataPointer)ent);
			cpSpaceAddStaticShape(getSpace(), edge);
		}*/
	}

	if(!strcmp(name, "platform 10"))
	{
		//cpShape * edge = NULL;

		entity_t * ent = initEnt();
		strcpy(ent->classname, "platform 10");
		ent->sprite = load("graphic/level/lvldesign/plvl5_10.png", 16, 32);
		ent->x = x;
		ent->y = y;
		ent->bBox.w = 16;
		ent->bBox.h = 32;
		ent->show = showEnt;

		SET_FLAG(ent->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
		{
			strcpy(ent->mode, "jekyll");
			SET_FLAG(ent->flags, ENT_FJEKYL);
		}

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(ent->flags, ENT_FHYDE);

		/*
		if (Game.gameState != GSTATE_LEVELEDIT)
		{
			edge = cpBoxShapeNew(cpSpaceGetStaticBody(getSpace()), 16, 32);
			edge->e = 0;
			edge->u = 0;
			cpBodySetPos(cpSpaceGetStaticBody(getSpace()), cpv(x, y));
			cpShapeSetCollisionType(edge, 1);
			cpShapeSetLayers(edge,CP_ALL_LAYERS);
			cpShapeSetUserData(edge, (const cpDataPointer)ent);
			cpSpaceAddStaticShape(getSpace(), edge);
		}*/
	}

	if (strcmp(name, "kid spawner") == 0)
	{
		entity_t * spawnerKid = initEnt ();

		strcpy(spawnerKid->classname, "kid spawner");

		spawnerKid->x = x;
		spawnerKid->y = y;
		spawnerKid->think = kidSpawnThink;
		spawnerKid->nextThink = getCurrentTime() + 70;

		SET_FLAG(spawnerKid->flags, ENT_SHOW); //might change this
	}

	if (strcmp(name, "bomber spawner") == 0)
	{
		entity_t * spawnerKid = initEnt ();

		strcpy(spawnerKid->classname, "bomber spawner");

		spawnerKid->x = x;
		spawnerKid->y = y;
		spawnerKid->think = bombSpawnThink;
		spawnerKid->nextThink = getCurrentTime() + 70;

		SET_FLAG(spawnerKid->flags, ENT_SHOW); //might change this
	}
}

void spawnParticle (int x, int y, float speed)
{
	entity_t * emitter = initEnt();
	sprintf(emitter->classname, "particle");

	emitter->x = x;
	emitter->y = y;

	emitter->sprite = load("graphic/particle/particle.png", 32, 32);
	emitter->show = showEnt;
	SET_FLAG(emitter->flags, ENT_SHOW);
	
	emitter->think = particleMove;
	emitter->nextThink = getCurrentTime() + 200;
}

//the emitter
void spawnMultiParticle (int x, int y, float speed)
{
	entity_t * emitter = initEnt();
	sprintf(emitter->classname, "particle");

	emitter->x = x;
	emitter->y = y;

	spawnParticle (x, y, speed);

	emitter->think = emitterThink;
	emitter->nextThink = getCurrentTime() + 200;
}