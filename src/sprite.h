#ifndef __SPRITE_H__
#define __SPRITE_H__

// Third-party library headers
#include <SDL.h>

/*
	Frames consists of the number representing which sprite in the sprite sheet to draw
	and how long to show that frame.
*/
struct Frame
{
	// frame number to determine what part of the spritesheet to show
	int frame; 

	// how long to show that frame
	int interval;
};

struct Animation
{
	// max number of frames
	struct Frame frames[64];

	// time before the next frame
	float m_timeBeforeNextFrame;

	// determines the current frame we are on
	int currentFrame;

	// how many frames are in this animation
	int numFrames;
};

struct Sprite
{
	// data representing the sprite
	SDL_Texture *m_sprite;

	// max numbers of animations
	struct Animation *m_animations;

	// texture, sprite, etc.
	int type;
};

#endif // !__SPRITE_H__
