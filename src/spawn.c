#include "include.h"

void spawnEntity(const char * name, float x, float y, const char * flag)
{
	if (strcmp(name, "kid") == 0)
	{
		entity_t * kid = Init_Ent();

		kid->sprite = load("graphic/enemy/kid.png", 32, 32);
		kid->x = x;
		kid->y = y;
		kid->bBox.w = 32;
		kid->bBox.h = 32;
		kid->show = show_Ent;
		kid->think = betaThink;
		kid->nextThink = getCurrentTime() + 7000;

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(kid->flags, ENT_FJEKYL);
		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(kid->flags, ENT_FHYDE);
		
		//set next think here
	}

	if (strcmp(name, "platform 1") == 0)
	{
		entity_t * platform1 = Init_Ent();

		platform1->sprite = load("graphic/level/lvldesign/plvl_1.png", 62, 24);
		platform1->x = x;
		platform1->y = y;
		platform1->bBox.w = 64;
		platform1->bBox.h = 64;
		platform1->show = show_Ent;

		//SDL_FillRect(getScreen(), &platform1->bBox, SDL_MapRGB(getScreen()->format, 0x77, 0x77, 0x77));

		SET_FLAG(platform1->flags, ENT_SOLID);

		if (strcmp(flag, "jekyll") == 0)
			SET_FLAG(platform1->flags, ENT_FJEKYL);

		if (strcmp(flag, "hyde") == 0)
			SET_FLAG(platform1->flags, ENT_FHYDE);

		//set next think here
	}
}