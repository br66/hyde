#include "include.h"
#include <stdio.h>

#include <yaml.h>

#include <jansson.h>
//#include <string.h>
//#include <stdlib.h>
#include <stdio.h>

static animSet_t loadedAnimSets [20]; //array of animation sets

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
// .anim format
// array of 20 arrays each element is s set of anims for that kind from .anim
// inuse


//JSON
static int newLine(const char *text)
{
	const char *newline = strchr(text, "\n");
	
	if (!newline)
		return strlen(text);
	else
		return (int)(newline - text);
}

void getSetFromFile (char *filename)
{
	/* for the forloops */
	int i, j, k;

	/* looks through file */
	json_t *parser;
	/* for errors */
	json_error_t error;

	/* parser looks through given file */
	parser = json_load_file(filename, 0, &error); //got file in parser
	
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

		printf("animation: %s \n \n", json_string_value(animation));	//json_string_value(animation) is the type of animation ex. idle
		printf("initial frame %d \n \n", json_integer_value(init));	//json_integer_value(init) is the frame the animation starts on

		/* now we print the frames that make up animation */
		printf("frames");
		/* frames' value should be an array of integers */
		frames = json_object_get(data, "frames");
		if (!json_is_array(frames))
		{
			fprintf(stderr, "next line should've been an array of frames");
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
			printf("	frame %d\n", json_integer_value(f_array)); //prints the current frame found in the file 
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
//disregard, inactive code
// do i want to make this void or do i want to return the data
void oldgetSetFromFile (char *filename)
{
	// new yaml parser
	// parse thru .yml file
	// translate, ready for loading
	
	/*FILE *file = fopen(filename, "r"); //open a readable file 

	yaml_parser_t parser; // open parser
	yaml_token_t token; // how to parse it

	char* currentToken;
	char** value;

	// parser start the dance
	if (!yaml_parser_initialize(&parser))
		fputs("NOPE\n", stderr);
	if (!file)
		fputs("Parser works, not the file\n", stderr);

	// File Set, gonna parse through that file
	yaml_parser_set_input_file(&parser, file);

	//Come Along, Do
	do
	{
		yaml_parser_scan (&parser, &token);  //read teh file
		switch (token.type)
		{
			// start the dance
			case YAML_STREAM_START_TOKEN: puts("Rolling staaaaaaaaarrt"); break;
			case YAML_STREAM_END_TOKEN: puts("GAME OVER YEEEEAAAAAAAHHH"); break;
			// main token types
			case YAML_KEY_TOKEN: printf("(key)  "); break;
			case YAML_VALUE_TOKEN: printf("(value) "); break;
			// block delimiters
			case YAML_BLOCK_SEQUENCE_START_TOKEN: puts("trigger to start a new block"); break;
			case YAML_BLOCK_ENTRY_TOKEN: puts("start block");
			case YAML_BLOCK_END_TOKEN: puts("end block");
			// actual data 
			case YAML_BLOCK_MAPPING_START_TOKEN: puts("[block mapping]"); break;
			case YAML_SCALAR_TOKEN: 
				currentToken = (char*)token.data.scalar.value; // current token
				
				if(!strcmp(currentToken, "maxFrames"))
				{
					//value = key's value
				}
				
				printf("billybob %s \n", token.data.scalar.value); break;
			
				
			
			// default stuff
			default:
				printf("got token of type %d\n", token.type);
		}

		if (token.type != YAML_STREAM_END_TOKEN)
			yaml_token_delete(&token);
	}
	while (token.type != YAML_STREAM_END_TOKEN);

	//setting fire to the rain
	yaml_token_delete (&token);

	yaml_parser_delete(&parser); // close
	fclose(file); */
}