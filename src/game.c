/* The game loop file */

#include "include.h"

entity_t *background;

static Uint32 delta = 0;
static Uint8 *keystates;

SDL_Event event;

static SDL_Color textColor = { 255, 255, 255 };

SDL_Rect health;
SDL_Rect anger;

extern entity_t* player;

extern entity_t *enemy1;
extern entity_t *enemy2;
extern entity_t *enemy3;

extern entity_t *boss;

extern entity_t *platform1;
extern entity_t *platform2;
extern entity_t *platform3;
extern entity_t *platform4;

extern entity_t *platformA1;
extern entity_t *platformA2;
extern entity_t *platformA3;
extern entity_t *platformA4;

extern entity_t *wall;

extern entity_t *lvlTrigger;

extern int level;

extern SDL_Surface *bossSprite;
//extern SDL_Surface *plyrSprite;

extern SDL_Surface *platformSprite1;
extern SDL_Surface *platformSpriteA1;

//extern animSet_t *playerAnim;

Uint32 start = 0;

bool done = false;
bool running = true;

/* create main or else (error LNK2001: unresolved external symbol _SDL_main) */
int main(int argc, char *argv[])
{	
	if ( init() == false)
		return 1;
	
	if ( load_Files() == false)
		return 1;

	/* [player] : initializaion, editing properties, getting the anim set, setting player state */
	player = Init_Ent();
	playerProperties(getPlayer());
	/* to put these in player properties, name change to initPlayer ? */ //#sprite
	//playerAnim = getAnimSet("sprite\\anim\\animsettest.json");
	//setStateTo(player, ANIM_IDLE);
	/* ------- */

	/* Enemy 1 */
	enemy1 = Init_Ent();
	sprintf(enemy1->classname, "enemy");
	
	enemy1->x = 600;
	enemy1->y = 350;

	enemy1->oldSprite = load_Image("sprite/char/enemy1.png"); //#sprite

	enemy1->think = alphaThink;
	enemy1->nextThink = getCurrentTime() + 5000;

	enemy1->bBox.w = 16;
	enemy1->bBox.h = 33;
	
	enemy1->show = show_Ent;
	/* ------- */

	/* Enemy 2 */
	enemy2 = Init_Ent();
	sprintf(enemy2->classname, "enemy");

	enemy2->oldSprite = load_Image("sprite/bluepng.png");

	enemy2->x = 770;
	enemy2->y = 350;

	//enemy2->bBox.w = 64;
	//enemy2->bBox.h = 64;

	enemy2->show = show_Ent;

	enemy2->think = betaThink;
	enemy2->nextThink = getCurrentTime() + 7000;
	/* ------- */

	/* Enemy 3 */
	enemy3 = Init_Ent();
	sprintf(enemy2->classname, "enemy");

	enemy3->oldSprite = load_Image("sprite/green.png");

	enemy3->x = 900;
	enemy3->y = 350;

	//enemy3->bBox.w = 64;
	//enemy3->bBox.h = 64;

	enemy3->show = show_Ent;

	enemy3->think = gammaThink;
	enemy3->nextThink = getCurrentTime() + 1000;
	/* ------- */

	/*  Boss  */
	boss = Init_Ent();

	boss->oldSprite = bossSprite;

	boss->x = 1000;
	boss->y = 300;

	//boss->bBox.w = 64;
	//boss->bBox.h = 64;

	boss->show = show_Ent;

	boss->think = bossThink;
	boss->nextThink = getCurrentTime() + 800;

	/* ------- */

	/* Wall */
	wall = Init_Ent();

	wall->oldSprite = load_Image("sprite/wall.jpg");

	wall->x = 400;
	wall->y = 40;

	wall->bBox.w = 75;
	wall->bBox.h = 100;

	//wall->think = wallThink;
	//wall->nextThink = currentTime + 10;

	/* ------- */

	//#sprite
	/* Define platforms */
	platform1 = Init_Ent();
	platform1->oldSprite = platformSprite1;
	platform1->x = 0;
	platform1->y = 410;
	platform1->bBox.w = 271;
	platform1->bBox.h = 56;
	platform1->show = show_Ent;

	platform2 = Init_Ent();
	platform2->oldSprite = platformSprite1;
	platform2->x = 271;
	platform2->y = 410;
	platform2->bBox.w = 271;
	platform2->bBox.h = 56;
	platform2->show = show_Ent;

	platform3 = Init_Ent();
	platform3->oldSprite = platformSprite1;
	platform3->x = 600;
	platform3->y = 410;
	platform3->bBox.w = 271;
	platform3->bBox.h = 56;
	platform3->show = show_Ent;

	platform4 = Init_Ent();
	platform4->oldSprite = platformSprite1;
	platform4->x = 871;
	platform4->y = 410;
	platform4->bBox.w = 271;
	platform4->bBox.h = 56;
	platform4->show = show_Ent;

	platformA1 = Init_Ent();
	platformA1->oldSprite = platformSpriteA1;
	platformA1->x = 0;
	platformA1->y = 410;
	platformA1->bBox.w = 271;
	platformA1->bBox.h = 56;
	platformA1->show = show_Ent;

	platformA2 = Init_Ent();
	platformA2->oldSprite = platformSpriteA1;
	platformA2->x = 271;
	platformA2->y = 410;
	platformA2->bBox.w = 271;
	platformA2->bBox.h = 56;
	platformA2->show = show_Ent;

	platformA3 = Init_Ent();
	platformA3->oldSprite = platformSpriteA1;
	platformA3->x = 600;
	platformA3->y = 410;
	platformA3->bBox.w = 271;
	platformA3->bBox.h = 56;
	platformA3->show = show_Ent;

	platformA4 = Init_Ent();
	platformA4->oldSprite = platformSpriteA1;
	platformA4->x = 900;
	platformA4->y = 410;
	platformA4->bBox.w = 271;
	platformA4->bBox.h = 56;
	platformA4->show = show_Ent;

	/* remove this
	lvlTrigger = Init_Ent();
	sprintf(lvlTrigger->classname, "trigger");
	lvlTrigger->x = 1100;
	lvlTrigger->y = 380;
	//lvlTrigger->oldSprite = plyrSprite;
	lvlTrigger->show = show_Ent; */

	/* HUD */
	health.x = 10;
	health.y = 10;
	health.w = (getPlayer()->currentHealth * 100) / getPlayer()->max_health; //how do I get rid of division? can I?
	health.h = 20;

	anger.x = 115;
	anger.y = 10;
	anger.w = (getPlayer()->currentAnger * 100) / getPlayer()->maxAnger;
	anger.h = 20;
	/* --- */

	start = SDL_GetTicks();

	level = 1; //initial level is 1 getLevel();

	/* GAME ------------------------------------------------------------------------- */
	// AiO function called Hyde(); ????
	do
	{	
		CheckLevel();
		EntityAlive();
		EntityShow();
		CheckCollisions();
		UpdateHealth();
		UpdateAnger();
		Events();
		PlayerAlive();

		SDL_FillRect ( getScreen(), &health, SDL_MapRGB ( getScreen()->format, 0, 0xFF, 0 ) );
		SDL_FillRect ( getScreen(), &anger, SDL_MapRGB ( getScreen()->format, 0x77, 0x77, 0x77 ) );

		//Function Time()
		if (running == true)
			{
				char msg[20];
				sprintf( msg, "%s", FormatTimeString(start));

				setUpSeconds(msg, textColor);
			}

		show_Ent(wall); //temp

		/* this gives us an array of all the possible keystates and whether a key is pressed or not */
		keystates = SDL_GetKeyState( NULL );

		/* delta time */
		delta = SDL_GetTicks() - getCurrentTime();

		/* Constantly getting the raw time from SDL */
		setCurrentTime();

		/* Function so that the screen is constantly updated so you can see things happening as they happen */
		SDL_Flip(getScreen());
	}
	
	while(!done);

	clear();

	exit(0);
	return 0;

	/* GAME -------------------------------------------------------------------------- */
}