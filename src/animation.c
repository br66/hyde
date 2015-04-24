#include <jansson.h>
#include "include.h"

// declarations
static animSet_t loadedAnimSets [MAX_SETS];

animSet_t *playerAnim = NULL;

// Initializing a new set of animations
animSet_t *InitAnimSet (void)
{
	int current;

	for (current = 0; current < MAX_SETS; current++)
	{
		if (loadedAnimSets[current].inuse == 0)
		{
			loadedAnimSets[current].inuse = 1;
			return &loadedAnimSets[current];
		}
	}

	// loadedAnimSets holds array of animationSets
	// each animation sets is an array of animation for one entity
	
	//need to go to every animation sets

	return NULL;
}



// File parsing - getting animation/animation sets from file --------------------------------------

animSet_t *getAnimSet (char *filename) //using data from file to populate object of type animation set, will return an animation set
{
	/* for the forloops */
	int i, j, k;

	/* creating blank animSet*/
	/* problem fixed, was missing asterisk */
	animSet_t *test = InitAnimSet();

	/* looks through file */
	json_t *parser;
	/* for errors */
	json_error_t error;

	/* parser is attached to given file */
	parser = json_load_file(filename, 0, &error);
	
	/* if couldn't get the file */
	if (!parser)
	{
		fprintf(stderr, "wtf no parser, file may not exist or be good fmt");
		return NULL;
	}
	
	/* reading file... */
	/* if the file doesn't start with an array */
	if (!json_is_array(parser))
	{
		fprintf(stderr, "didn't find an array\n");
		json_decref(parser);
		return NULL;
	}

	/* looks through array of objects */
	for (i = 0; i < json_array_size(parser); i++)
	{
		json_t *data, *animation, *init, *frames, *f_array, *intervals, *i_array;

		/* f_array and i_array are incorrectly named, they're actually the current value found in their respective arrays */

		/* gets objects in array, ex. if i = 1, we are getting first object in array */
		data = json_array_get(parser, i);
		if(!json_is_object(data))
		{
			fprintf(stderr, "next line should've been an object");
			json_decref(parser);
			return NULL;
		}

		/* the first key should be "animation" for animation type */
		animation = json_object_get(data, "animation");
		if(!json_is_string(animation))
		{
			fprintf(stderr, "next line should've been an animation value");
			json_decref(parser);
			return NULL;
		}

		/* the second key is for the initial frame for the animation */
		init = json_object_get(data, "init");
		if(!json_is_integer(init))
		{
			fprintf(stderr, "next line should've been an inital frame value");
			json_decref(parser);
			return NULL;
		}

		/* prints animation type and initial frame */
		printf("animation: %s \n \n", json_string_value(animation));	//json_string_value(animation) is the type of animation ex. idle, THIS RETURNS CHAR
		printf("initial frame %d \n \n", json_integer_value(init));	//json_integer_value(init) is the frame the animation starts on, WARNING THIS RETURN LOOOOONG
		test->set[0].curFrame = 0;

		/* now we print the frames that make up animation */
		printf("frames");
		/* frames' value should be an array of integers */
		frames = json_object_get(data, "frames");
		if (!json_is_array(frames))
		{
			fprintf(stderr, "next line should've been an array of frames/integers");
			json_decref(parser);
			return NULL;
		}

		/* use for loop to get every single integer/frame */
		for (j=0; j < 10; j++) //goes through "frames" which is an array of frames that make up the animation, there will always be 10 frames
		{
			f_array = json_array_get(frames, j);
			if (!json_is_integer(f_array))
			{
				fprintf(stderr, "can't find array or next number...");
				json_decref(parser);
				return NULL;
			}
			printf("	frame %d\n", json_integer_value(f_array));		//prints the current frame found in the file 
			test->set[0].frames[j] = (short)json_integer_value(f_array);
		}

		/* lastly, we get the intervals which are how may milliseconds each frame is shown */
		printf("\nintrvls");
		intervals = json_object_get(data, "intervals");
		if(!json_is_array(intervals))
		{
			fprintf(stderr, "can't get value of intervals");
			json_decref(parser);
			return NULL;
		}

		/* use for loop to get every single integer/frame */
		for (k=0; k < 10; k++) //goes through "frames" which is an array of frames that make up the animation, there will always be 10 frames
		{
			i_array = json_array_get(intervals, k);
			if (!json_is_integer(i_array))
			{
				fprintf(stderr, "can't find array or next number...");
				json_decref(parser);
				return NULL;
			}
			printf("	%d milliseconds\n", json_integer_value(i_array)); //prints the current frame found in the file
			test->set[0].intervals[k] = (int)json_integer_value(i_array);
			test->set[0].maxFrames = 10; //for testing
			test->set[0].nextFrameTime = 100; //for testing
		}
	}

	json_decref(parser);
	return test; //address
}



// Animating -----------------------------------------------------------------------------------

/* Animation motor */ //#sprite
void Animate (SDL_Surface* spritesheet, animation_t *animation, float x, float y) //missing asterisk in front 
{
	if(animation->nextFrameTime <= getCurrentTime()) //if time for next frame has passed
	{
		animation->curFrame = animation->frames[animation->frameCounter];
		if (animation->curFrame >= animation->maxFrames) //if reached end of frames, go back 
		{
			animation->curFrame = 0;
		}

		if (animation->frameCounter >= animation->maxFrames)
		{
			animation->frameCounter = 0;
		}

		//frame = (frame + 1) % animation.maxFrames;
	
		animation->nextFrameTime = animation->intervals[animation->curFrame] + getCurrentTime(); //find the next frame time
		showFrame(spritesheet, getScreen(), x, y, animation->frames[animation->curFrame]); //draws to surface only once
		//#sprite?
		//printf("%d \n", animation->curFrame);
		animation->frameCounter++;
	}

	showFrame(spritesheet, getScreen(), x, y, animation->frames[animation->curFrame]); //draws to surface only once
}