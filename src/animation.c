#include <jansson.h>
#include "include.h"
//#include <chipmunk.h>

//Object type declarations
static animSet_t loadedAnimSets [MAX_SETS];


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

void getAnimSet (char *filename) //using data from file to populate object of type animation set, will return an animation set
{
	/* for the forloops */
	int i, j, k;

	/* creating blank animSet, UNHANDLED EXCEPTION AT LINE 132, ADDRESS IS ILLEGAL, PUT IN ARRAY */
	/* problem fixed, was missing asterisk, must make it null otherwise uninitialized, needs to be in loadedAnimSets */
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
		return;
	}
	
	/* reading file... */
	/* if the file doesn't start with an array */
	if (!json_is_array(parser))
	{
		fprintf(stderr, "didn't find an array\n");
		json_decref(parser);
		return;
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
			return;
		}

		/* the first key should be "animation" for animation type */
		animation = json_object_get(data, "animation");
		if(!json_is_string(animation))
		{
			fprintf(stderr, "next line should've been an animation value");
			json_decref(parser);
			return;
		}

		/* the second key is for the initial frame for the animation */
		init = json_object_get(data, "init");
		if(!json_is_integer(init))
		{
			fprintf(stderr, "next line should've been an inital frame value");
			json_decref(parser);
			return;
		}

		/* prints animation type and initial frame */
		printf("animation: %s \n \n", json_string_value(animation));	//json_string_value(animation) is the type of animation ex. idle, THIS RETURNS CHAR
		printf("initial frame %d \n \n", json_integer_value(init));	//json_integer_value(init) is the frame the animation starts on, WARNING THIS RETURN LOOOOONG

		/* now we print the frames that make up animation */
		printf("frames");
		/* frames' value should be an array of integers */
		frames = json_object_get(data, "frames");
		if (!json_is_array(frames))
		{
			fprintf(stderr, "next line should've been an array of frames/integers");
			json_decref(parser);
			return;
		}

		/* use for loop to get every single integer/frame */
		for (j=0; j < 10; j++) //goes through "frames" which is an array of frames that make up the animation, there will always be 10 frames
		{
			f_array = json_array_get(frames, j);
			if (!json_is_integer(f_array))
			{
				fprintf(stderr, "can't find array or next number...");
				json_decref(parser);
				return;
			}
			printf("	frame %d\n", json_integer_value(f_array));		//prints the current frame found in the file 
			test->set[0].frames[j] = (int)json_integer_value(f_array); //game currently breaks here, set[0] is at 0x00, must be initialized
																		//test->set[0] = InitSingleAnimation() put where?
																		// create new animation_t put in set?
		}

		/* lastly, we get the intervals which are how may milliseconds each frame is shown */
		printf("\nintrvls");
		intervals = json_object_get(data, "intervals");
		if(!json_is_array(intervals))
		{
			fprintf(stderr, "can't get value of intervals");
			json_decref(parser);
			return;
		}

		/* use for loop to get every single integer/frame */
		for (k=0; k < 10; k++) //goes through "frames" which is an array of frames that make up the animation, there will always be 10 frames
		{
			i_array = json_array_get(intervals, k);
			if (!json_is_integer(i_array))
			{
				fprintf(stderr, "can't find array or next number...");
				json_decref(parser);
				return;
			}
			printf("	%d milliseconds\n", json_integer_value(i_array)); //prints the current frame found in the file 
		}
	}

	json_decref(parser);
	return; //return an entire animation set?
}



// Animating -----------------------------------------------------------------------------------

/* Animation motor */
void Animate (SDL_Surface* spritesheet, animation_t animation, float x, float y)
{
	if(animation.nextFrameTime <= getCurrentTime()) //if time for next frame has passed
	{
		animation.frame++; //move frame by 1
		if (animation.frame >= animation.maxFrames)//if reached end of frames, go back 
			animation.frame = 0;
		//frame = (frame + 1) % animation.maxFrames;
		animation.nextFrameTime = animation.intervals[animation.frame] + getCurrentTime(); //find the next frame time
		showFrame(spritesheet, getScreen(), x, y, animation.frames[animation.frame]);
	}
}