#ifndef _ANIMATION_
#define _ANIMATION_

#define MAX_ANIMATIONS 20 //maximum animations in set

// an individual animation
typedef struct animation_s
{
	int refNum; //each animation in the set has a reference number

	short frames[10]; //frames that are part of the animation
	int intervals[10]; //how long each frame is displayed

	int frame; //current frame
	int maxFrames; //maximum amount of frames

	void* parent; //pointer to address of which anination set this animation came from void to fix circular dependency

	int nextFrameTime; //time for the next frame to show

}animation_t;

// an array of animations
typedef struct animSet_s
{
	int inuse;
	animation_t* set[MAX_ANIMATIONS]; //Circular typedef dependency resolved

}animSet_t;

void Animate (SDL_Surface* spritesheet, animation_t animation, float x, float y); //actual action of animation

void getSetFromFile (char *filename); //will find anim set file and see if loaded already, add it to array of loaded ones
void displayFromFile (char *filename); // will check if displayed already, if not, then display


#endif