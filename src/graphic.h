/**********************************************************************************************//**
 * @file	src\graphic.h
 *
 * @brief	Sprites/spritesheets/animation/game screen/game camera
 **************************************************************************************************/

// include
#include "boolean.h"

#ifndef _GRAPHIC_
#define _GRAPHIC_

// #define CAMERA | SCREEN
#define	BITSPERPIXEL	32
#define	SCREEN_WIDTH	640 
#define	SCREEN_HEIGHT	480
#define L_WIDTH			1920
#define	L_HEIGHT		1200

// #define GRAPHICS
#define MAX_SPRITES		50
#define MAX_SETS		20
#define MAX_ANIMATIONS	20

// structures and types
typedef struct animation_s
{
	int refNum; //each animation in the set has a reference number, move to animation set?

	int frameCounter; //to look through array
	short frames[10]; //frames that are part of the animation
	int intervals[10]; //how long each frame is displayed

	int curFrame; //current frame
	int maxFrames; //maximum amount of frames

	void* parent; //pointer to address of which anination set this animation came from void to fix circular dependency

	int nextFrameTime; //time for the next frame to show

}animation_t;

typedef struct animset_s
{
	int inuse; //refnum?
	animation_t set[MAX_ANIMATIONS];  // was doing a pointer when i didn't need one, force of habit

}animset_t;

typedef struct sprite_s
{
	SDL_Surface		*graphic; //can be a single sprite or a spritesheet
	animset_t		*animationSet; //each sprite has a set of animaitions associated with it
	char			filename[40];
	int				width, height;
	int				framesperline;
	int				used; //reference count

}sprite_t;

// functions for sprite_t
void initSprites ();
void closeSprites ();

sprite_t* load (char *filename, int width, int height);
void freeSprite (sprite_t * sprite);
void show_Surface (float x, float y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip); // needed by setUpSeconds()
void showFrame (SDL_Surface* spritesheet, SDL_Surface* surface, float sx, float sy, int frame); // needed for animation
void surface (sprite_t * source, SDL_Surface * destination, float x, float y, SDL_Rect * clip);

// functions for screen/game window
bool setupScreen ();
SDL_Surface* getScreen ();
void closeScreen ();

// functions for animation
animset_t *getAnimSet (char *filename); //will find anim set file and see if loaded already, add it to array of loaded ones
animset_t *InitAnimSet(void);
void Animate (sprite_t * spritesheet, animation_t *animation, float x, float y);

#endif