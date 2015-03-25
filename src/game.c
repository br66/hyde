/* The game loop file */

#include "include.h"

/* entities */
//entity_t *wall;
//entity_t *player;
entity_t *background;

/* create main or else (error LNK2001: unresolved external symbol _SDL_main) */
int main(int argc, char *argv[])
{
	//check level function
	/* if level one, show these things */
	/* if level two, show these things */
	
	bool done = false;

	/* Starting time for the timer */
	Uint32 start = 0;

	/* Flag for if the timer is running or not */
	bool running = true;
	
	/* Start everything (SDL, open window, etc.), make sure done successfully */
	if ( init() == false)
	{
		return 1;
	}
	
	/* Load all the file, check if done successfully */
	if ( load_Files() == false)
	{
		return 1;
	}
	
	/* Might move this */
	start = SDL_GetTicks();

	/* HUD */
	health.x = 10;
	health.y = 10;
	health.w = 100;
	health.h = 35;

	anger.x = 115;
	anger.y = 10;
	anger.w = 100;
	anger.h = 35;
	/* --- */

	/* PLAYER */
	player = Init_Ent();
	player->resetPosition = init_Position;
	player->handle_Input = handle_Input;
	player->move = move;
	player->show = show;

	init_Position(player);

	//init player function????

	SET_FLAG(player->flags, ENT_SOLID);
	/* ------- */

	/* Enemy 1 */
	enemy1 = Init_Ent();
	sprintf(enemy1->classname, "enemy");
	
	enemy1->x = 600;
	enemy1->y = 350;

	enemy1->sprite = load_Image("sprite/red.png"); //sprites will later be loaded in sprite.c // declared in sprite.h

	enemy1->think = alphaThink;
	enemy1->nextThink = currentTime + 5000;

	enemy1->bBox.w = 64;
	enemy1->bBox.h = 64;
	
	enemy1->show = show_Enemy;
	/* ------- */

	/* Enemy 2 */
	enemy2 = Init_Ent();
	sprintf(enemy2->classname, "enemy");

	enemy2->sprite = load_Image("sprite/bluepng.png");

	enemy2->x = 770;
	enemy2->y = 350;

	//enemy2->bBox.w = 64;
	//enemy2->bBox.h = 64;

	enemy2->show = show_Enemy;

	enemy2->think = betaThink;
	enemy2->nextThink = currentTime + 7000;
	/* ------- */

	/* Enemy 3 */
	enemy3 = Init_Ent();
	sprintf(enemy2->classname, "enemy");

	enemy3->sprite = load_Image("sprite/green.png");

	enemy3->x = 900;
	enemy3->y = 350;

	//enemy3->bBox.w = 64;
	//enemy3->bBox.h = 64;

	enemy3->show = show_Enemy;

	enemy3->think = gammaThink;
	enemy3->nextThink = currentTime + 1000;
	/* ------- */

	/*  Boss  */
	boss = Init_Ent();

	boss->sprite = bossSprite;

	boss->x = 1000;
	boss->y = 300;

	boss->show = show_Enemy;

	boss->think = bossThink;
	boss->nextThink = currentTime + 800;

	/* ------- */

	/* Wall */
	wall = Init_Ent();

	wall->sprite = load_Image("sprite/wall.jpg");

	wall->x = 400;
	wall->y = 40;

	wall->bBox.w = 75;
	wall->bBox.h = 100;

	wall->think = wallThink;
	wall->nextThink = currentTime + 10;

	/* ------- */

	/* Define platforms */
	platform1 = Init_Ent();
	platform1->sprite = platformSprite1;
	platform1->x = 0;
	platform1->y = 410;
	platform1->bBox.w = 271;
	platform1->bBox.h = 56;
	platform1->show = show_Enemy;

	platform2 = Init_Ent();
	platform2->sprite = platformSprite1;
	platform2->x = 271;
	platform2->y = 410;
	platform2->bBox.w = 271;
	platform2->bBox.h = 56;
	platform2->show = show_Enemy;

	platform3 = Init_Ent();
	platform3->sprite = platformSprite1;
	platform3->x = 600;
	platform3->y = 410;
	platform3->bBox.w = 271;
	platform3->bBox.h = 56;
	platform3->show = show_Enemy;

	platform4 = Init_Ent();
	platform4->sprite = platformSprite1;
	platform4->x = 871;
	platform4->y = 410;
	platform4->bBox.w = 271;
	platform4->bBox.h = 56;
	platform4->show = show_Enemy;

	platformA1 = Init_Ent();
	platformA1->sprite = platformSpriteA1;
	platformA1->x = 0;
	platformA1->y = 410;
	platformA1->bBox.w = 271;
	platformA1->bBox.h = 56;
	platformA1->show = show_Enemy;

	platformA2 = Init_Ent();
	platformA2->sprite = platformSpriteA1;
	platformA2->x = 271;
	platformA2->y = 410;
	platformA2->bBox.w = 271;
	platformA2->bBox.h = 56;
	platformA2->show = show_Enemy;

	platformA3 = Init_Ent();
	platformA3->sprite = platformSpriteA1;
	platformA3->x = 600;
	platformA3->y = 410;
	platformA3->bBox.w = 271;
	platformA3->bBox.h = 56;
	platformA3->show = show_Enemy;

	platformA4 = Init_Ent();
	platformA4->sprite = platformSpriteA1;
	platformA4->x = 900;
	platformA4->y = 410;
	platformA4->bBox.w = 271;
	platformA4->bBox.h = 56;
	platformA4->show = show_Enemy;

	lvlTrigger = Init_Ent();
	sprintf(lvlTrigger->classname, "trigger");
	lvlTrigger->x = 1100;
	lvlTrigger->y = 380;
	lvlTrigger->sprite = plyrSprite;
	//lvlTrigger->fill.x = lvlTrigger->x;
	//lvlTrigger->fill.y = lvlTrigger->y;
	lvlTrigger->bBox.w = 20;
	lvlTrigger->bBox.h = 20;
	lvlTrigger->show = show_Enemy;

	level = 1; // when the game starts, we will be at level 1

	/* GAME ------------------------------------------------------------------------- */
	do
	{
		CheckLevel();
		EntityAlive();
		EntityShow();
		CheckCollisions();

		while (SDL_PollEvent (&event))
		{
			handle_Input(player);

			if ( event.type == SDL_KEYDOWN )
			{
				switch ( event.key.keysym.sym )
				{
					case SDLK_UP: 
						if (Mix_PlayChannel (-1, scratch, 0) == -1) //arg. 1, -1 means looking for the next sound channel available		//arg. 2, sound that will be played
							return 1;								//arg. 3, how many times sound will loop
						break;
					case SDLK_1:
						if (level != 1)
						{
							level = 1;

							//enemy 1 initial position
							enemy1->x = 600;
							enemy1->y = 350;
							enemy1->thinkflags = 0;
							enemy1->xVel = 0;

							//enemy 2 initial position
							enemy2->x = 770;
							enemy2->y = 350;
							enemy2->thinkflags = 0;
							enemy2->xVel = 0;

							//enemy 3 initial position
							enemy3->x = 900;
							enemy3->y = 350;
							enemy3->thinkflags = 0;
							enemy3->xVel = 0;
							enemy3->yVel = 0;

							//boss 3 initial position
							//boss->x = 1000;
							//boss->y = 300;
							//boss->thinkflags = 0;
							//boss->xVel = 0;
							//boss->yVel = 0;
						}
						break;
					case SDLK_2:
						if (level != 2)
						{
							level = 2;

							//enemy 1 initial position, just in case
							enemy1->x = 600;
							enemy1->y = 350;
							enemy1->thinkflags = 0;
							enemy1->xVel = 0;

							//enemy 2 initial position, just in case
							enemy2->x = 770;
							enemy2->y = 350;
							enemy2->thinkflags = 0;
							enemy2->xVel = 0;

							//enemy 3 initial position, just in case
							enemy3->x = 900;
							enemy3->y = 350;
							enemy3->thinkflags = 0;
							enemy3->xVel = 0;
							enemy3->yVel = 0;

							//boss 3 initial position
							//boss->x = 1000;
							//boss->y = 300;
							//boss->thinkflags = 0;
							//boss->xVel = 0;
							//boss->yVel = 0;
						}
						break;
					case SDLK_RIGHT:
						if (Mix_PlayChannel (-1, low, 0) == -1)
							return 1;
						break;
					case SDLK_s:
						if (running == true)
						{
							running = false;
							start = 0;
						}
						else
						{
							running = true;
							start = SDL_GetTicks();
						}
					}
				}

			//If the user presses Quit (the x button on the window)
			if(event.type == SDL_QUIT)
			{
				//Game is done
				done = true;
			}
		}
		move(player);
		set_Camera(player);

		if (running == true)
			{
				char msg[20];
				sprintf( msg, "%s", FormatTimeString(start));

				seconds = TTF_RenderText_Solid (font, msg, textColor);
				show_Surface ((SCREEN_WIDTH - (float)seconds->w ) / 2, 50, seconds, screen, NULL);

				SDL_FreeSurface( seconds );
			}

		show(player);

		show_Enemy(wall);

		SDL_FillRect ( screen, &health, SDL_MapRGB ( screen->format, 0, 0xFF, 0 ) );
		SDL_FillRect ( screen, &anger, SDL_MapRGB ( screen->format, 0x77, 0x77, 0x77 ) );

		if (IS_SET(lvlTrigger->flags, ENTFLAG_SHOW))
		{
			SDL_FillRect ( screen, &lvlTrigger->fill, SDL_MapRGB ( screen->format, 0x77, 0x77, 0x77 ) );
		}
		

		/* this gives us an array of all the possible keystates and whether a key is pressed or not */
		keystates = SDL_GetKeyState( NULL );

		delta = SDL_GetTicks() - currentTime;

		/* Constantly getting the raw time from SDL */
		currentTime = SDL_GetTicks();

		/* Function so that the screen is constantly updated so you can see things happening as they happen */
		SDL_Flip(screen);
	}
	
	while(!done);

	clear();

	exit(0);
	return 0;

	/* GAME -------------------------------------------------------------------------- */
}