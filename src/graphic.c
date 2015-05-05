// #include
#include <SDL.h>
#include <SDL_image.h>
#include <jansson.h>

#include "graphic.h"
#include "gfunc.h"

// declarations for screen/game window
static SDL_Surface *screen = NULL; //main screen, menu and game backgrounds will be here
static SDL_Surface *levelscreen = NULL; //entities will be here, background will be excluded for parallax

// declarations for sprites
sprite_t listSprites[MAX_SPRITES]; // similar to listEntities, keeps track of how many sprites have been loaded
int numSprites;

// declarations for animation
animset_t loadedAnimSets [MAX_SETS]; // similar to listEntities, keeps track of how many animation sets are loaded
int numSets;

// for the entire list, give me that fresh 0x00!
void initSprites ()
{
	int i; numSprites = 0;

	memset(listSprites,0,sizeof(sprite_t) * MAX_SPRITES); //gets 50 blocks of memory

	for (i = 0; i < MAX_SPRITES; i++)
	{
		listSprites[i].graphic = NULL;
		listSprites[i].animationSet = NULL;
		listSprites[i].framesperline = 0;
		listSprites[i].height = 0;
		listSprites[i].width = 0;
		listSprites[i].used = 0;
	}
}

// free all sprites from the list
void closeSprites ()
{
	int i;

	for (i = 0; i < MAX_SPRITES; i++)
		freeSprite(&listSprites[i]);
}

// load sprite from file
sprite_t* load (char *filename, int width, int height)
{
	int i;
	SDL_Surface * temp;

	/* searching thru list of loaded sprites to check if i already have the file asked for loaded */
	for (i = 0; i < numSprites; i++)
	{
		if (strncmp(filename, listSprites[i].filename, 20) == 0)
		{
			listSprites[i].used++;
			return &listSprites[i];
		}
	}

	/* do we have room? */
	if(numSprites + 1 >= MAX_SPRITES)
	{
		fprintf(stderr, "Maximum Sprites Reached. \n");
		exit(0);
	}
	
	/* you made it this far kid, now time for the real stuff */
	numSprites++;

	/* if i find one that isn't used break */
	for (i=0; i <= numSprites; i++)
		if(!listSprites[i].used)break;
		
	temp = IMG_Load(filename);
	if (temp == NULL)
	{
		fprintf(stderr, "no sprite: %s \n", SDL_GetError());
		exit(0);
	}

	// setting [i]'s image
	listSprites[i].graphic = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	SDL_SetColorKey(listSprites[i].graphic, SDL_SRCCOLORKEY, SDL_MapRGB(listSprites[i].graphic->format, 255, 255, 255));

	// setting [i]'s filename
	strncpy(listSprites[i].filename, filename, 40);
	
	/* depending on their filename, function will determine if sprite is high 
	or low priority if you have platform in your name, most likely high
	if you're specific to one level, low priority and expendable gotta find 
	function that only searches through some of the char array may also include 
	what levels they belong to */

	listSprites[i].framesperline = 16;
	listSprites[i].width = width;
	listSprites[i].height = height;
	listSprites[i].used++;
	
	return &listSprites[i];
}

// free individual sprite from memory
void freeSprite (sprite_t * sprite)
{
	if (sprite->used < 0)
		sprite->used = 0;
	else
		sprite->used--;

	//remove?
	if (sprite->used == 0)
	{
		strcpy(sprite->filename, "\0"); // clears the filename string
		
		if (sprite->graphic != NULL)
			SDL_FreeSurface(sprite->graphic);
		
		sprite->graphic = NULL;
	}
}

// old function for blitting surfaces to screen - to remove, 1 dependency (void setUpSeconds, game.c, line 264 approx.)
void show_Surface (float x, float y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;

	offset.x = (int)x;
	offset.y = (int)y;

	SDL_BlitSurface( source, clip, destination, &offset);
}
// shows individual frame for animation - may be absorbed into animate function
void showFrame (SDL_Surface* spritesheet, SDL_Surface* surface, float sx, float sy, int frame) // to get entity and its framesperline for its sprite
{
	SDL_Rect source, dest;

	source.x = (frame * 32) % 320;
	source.y = (frame * 32) / 320;
	source.w = 32;
	source.h = 32;

	dest.x = (int)sx;
	dest.y = (int)sy;
	dest.w = 32;
	dest.h = 32;

	SDL_BlitSurface (spritesheet, &source, surface, &dest); //#sprite
}

// new function for blitting sprites to the game surface
void surface (sprite_t * source, SDL_Surface * destination, float x, float y, SDL_Rect * clip)
{
	SDL_Rect offset;

	offset.x = (int)x;
	offset.y = (int)y;

	SDL_BlitSurface( source->graphic, clip, destination, &offset);
}

// functions for screen/game window
bool setupScreen()
{
	/*Uint32 viewFlags = SDL_ANYFORMAT | SDL_SRCALPHA;
	Uint32 hwFlags = 0;
	
	if (SDL_VideoModeOK(1024, 600, 32, viewFlags | SDL_HWSURFACE))
	{

	}*/
	
	screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, BITSPERPIXEL, SDL_SWSURFACE);
	if (screen == NULL)
	{
		return false;
	}
	return true;
}

// get function for files that want the screen, but can't access it normally
SDL_Surface* getScreen (void)
{
	return screen;
}

// get rid of the screen, usually used for the end of game
void closeScreen(void)
{
	SDL_FreeSurface (screen);
}

// functions for animation
animset_t *InitAnimSet (void)
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

	return NULL;
}

animset_t *getAnimSet (char *filename)
{
	int i, j, k;

	animset_t *test = InitAnimSet();

	json_t *parser;
	json_error_t error;

	parser = json_load_file(filename, 0, &error);
	if (!parser)
	{
		fprintf(stderr, "wtf no parser, file may not exist or be good fmt");
		return NULL;
	}
	if (!json_is_array(parser))
	{
		fprintf(stderr, "didn't find an array\n");
		json_decref(parser);
		return NULL;
	}

	for (i = 0; i < json_array_size(parser); i++)
	{
		json_t *data, *animation, *init, *frames, *f_array, *intervals, *i_array;

		/* f_array and i_array are incorrectly named, they're actually the current value found in their respective arrays */

		data = json_array_get(parser, i);
		if(!json_is_object(data))
		{
			fprintf(stderr, "next line should've been an object");
			json_decref(parser);
			return NULL;
		}

		animation = json_object_get(data, "animation");
		if(!json_is_string(animation))
		{
			fprintf(stderr, "next line should've been an animation value");
			json_decref(parser);
			return NULL;
		}

		init = json_object_get(data, "init");
		if(!json_is_integer(init))
		{
			fprintf(stderr, "next line should've been an inital frame value");
			json_decref(parser);
			return NULL;
		}

		//printf("animation: %s \n \n", json_string_value(animation));	//json_string_value(animation) is the type of animation ex. idle, THIS RETURNS CHAR
		//printf("initial frame %d \n \n", json_integer_value(init));	//json_integer_value(init) is the frame the animation starts on, WARNING THIS RETURN LOOOOONG
		
		test->set[0].curFrame = 0;

		//printf("frames");
		frames = json_object_get(data, "frames");
		if (!json_is_array(frames))
		{
			fprintf(stderr, "next line should've been an array of frames/integers");
			json_decref(parser);
			return NULL;
		}

		for (j=0; j < 10; j++)
		{
			f_array = json_array_get(frames, j);
			if (!json_is_integer(f_array))
			{
				fprintf(stderr, "can't find array or next number...");
				json_decref(parser);
				return NULL;
			}
			//printf("	frame %d\n", json_integer_value(f_array));
			test->set[0].frames[j] = (short)json_integer_value(f_array);
		}
		
		//printf("\nintrvls");
		intervals = json_object_get(data, "intervals");
		if(!json_is_array(intervals))
		{
			fprintf(stderr, "can't get value of intervals");
			json_decref(parser);
			return NULL;
		}

		for (k=0; k < 10; k++)
		{
			i_array = json_array_get(intervals, k);
			if (!json_is_integer(i_array))
			{
				fprintf(stderr, "can't find array or next number...");
				json_decref(parser);
				return NULL;
			}
			//printf("	%d milliseconds\n", json_integer_value(i_array)); //prints the current frame found in the file
			test->set[0].intervals[k] = (int)json_integer_value(i_array);
		}

		test->set[0].maxFrames = 10; //for testing
		test->set[0].nextFrameTime = 100; //for testing
	}

	json_decref(parser);
	return test; //address
}

// motor for animating
void Animate (sprite_t * spritesheet, animation_t *animation, float x, float y)
{
	if(animation->nextFrameTime <= getCurrentTime()) 
	{
		animation->curFrame = animation->frames[animation->frameCounter];
		if (animation->curFrame >= animation->maxFrames)
		{
			animation->curFrame = 0;
		}

		if (animation->frameCounter >= animation->maxFrames)
		{
			animation->frameCounter = 0;
		}

		//frame = (frame + 1) % animation.maxFrames;
	
		animation->nextFrameTime = animation->intervals[animation->curFrame] + getCurrentTime();

		//printf("%d \n", animation->curFrame);

		animation->frameCounter++;
	}

	// actually shows the new frame
	showFrame(spritesheet->graphic, getScreen(), x, y, animation->frames[animation->curFrame]);
}