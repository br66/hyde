/**********************************************************************************************//**
 * @file	src\gfunc.h
 *
 * @brief	Declares the gfunc class.  Used to populate with functions and variables that the
 * 			game class and gameloop rely on and to make the game class easier to read.
 **************************************************************************************************/

#ifndef _FUNC_
#define _FUNC_



/* Includes */

#include <SDL_ttf.h>
#include "graphic.h" // entity header dependent on graphic header
#include "entity.h" // needed for camera function



/* Defines */

// for time-keeping
#define TIMEUNIT_HOURS		3
#define TIMEUNIT_MINUTES	2
#define TIMEUNIT_SECONDS	1
#define TIMEUNIT_HUNDRETHS	0



/* Enumerations */

// for the game state machine
enum gameState
{
	GSTATE_MENU,
	GSTATE_LEVELEDIT,
	GSTATE_LEVEL1,
	GSTATE_LEVEL2,
	GSTATE_GAMEOVER,
	GSTATE_BOSS
};

// for the level state machine
enum levelState
{
	NO_MODE,
	JEKYLL_MODE,
	HYDE_MODE
};


/* Structures/Types */

// game structure for the game state machine
typedef struct game_s
{
	int gameState;
	int levelState;

}game_t;



/* Functions */

// for beginning and end of game
void begin();
void end();

// for setting the game state
void setGameState (int gameState);
void setLvlState (int levelState);

// for loading levels
void loadLevel(char * level);

/* gets, sets, and closers to reduce amount of externs */
SDL_Rect getCamera (void);
void cameraSetOn( entity_t *ent);
SDL_Rect *addrCamera (void);

TTF_Font *getFont (void);

Uint32 getCurrentTime (void);
void setCurrentTime(void);

SDL_Surface *getSeconds(void);
void setUpSeconds(char* msg, SDL_Color textColor);
void closeSeconds(void);

SDL_Event getEvents();

// for the player and hud
void UpdateHealth();
void UpdateAnger();

// for game events (ex. keyboard input)
void Events(void); // name must be changed

/* for time */
char* FormatTimeString(Uint32 offset);
char* timeString(Uint32 offset);

/* obsolete func */
void clear();
#endif