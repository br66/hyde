#include "include.h"
#include <stdio.h>
#include <yaml.h>

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


// do i want to make this void or do i want to return the data
void getSetFromFile (char *filename)
{
	// new yaml parser
	// parse thru .yml file
	// translate, ready for loading
	
	FILE *file = fopen(filename, "r"); //open a readable file 

	yaml_parser_t parser; // open parser
	yaml_token_t token; // how to parse it
	//printf("idle state");
	/* parser start the dance */
	if (!yaml_parser_initialize(&parser))
		fputs("NOPE\n", stderr);
	if (!file)
		fputs("Parser works, not the file\n", stderr);

	/* File Set, gonna parse through that file */
	yaml_parser_set_input_file(&parser, file);

	/* Come Along, Do */
	do
	{
		yaml_parser_scan (&parser, &token);
		switch (token.type)
		{
			/* start the dance */
			case YAML_STREAM_START_TOKEN: puts("Rolling staaaaaaaaarrt"); break;
			case YAML_STREAM_END_TOKEN: puts("GAME OVER YEEEEAAAAAAAHHH"); break;
			/* main token types */
			case YAML_KEY_TOKEN: printf("(key)  "); break;
			case YAML_VALUE_TOKEN: printf("(value) "); break;
			/* block delimiters */
			case YAML_BLOCK_SEQUENCE_START_TOKEN: puts("trigger to start a new block"); break;
			case YAML_BLOCK_ENTRY_TOKEN: puts("start block");
			case YAML_BLOCK_END_TOKEN: puts("end block");
			/* actual data */
			case YAML_BLOCK_MAPPING_START_TOKEN: puts("[block mapping]"); break;
			case YAML_SCALAR_TOKEN: printf("billybob %s \n", token.data.scalar.value); break;
			/* default stuff */
			default:
				printf("got token of type %d\n", token.type);
		}

		if (token.type != YAML_STREAM_END_TOKEN)
			yaml_token_delete(&token);
	}
	while (token.type != YAML_STREAM_END_TOKEN);

	yaml_token_delete (&token);

	yaml_parser_delete(&parser); // close
	fclose(file);

	printf("idle state");
}