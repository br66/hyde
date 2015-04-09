
/* For this commit, global.h and global.c have been removed.
The objects and variables declared in assets.c and .h are
being gradually removed and replaced with specific get
and set functions in their respective headers/c files.
For example "extern SDL_Surface *camera has been replaced
with getCamera(). and camera is now static so its value
cannot be changed outside where it is declared. */

//THE FOLLOWING CANNOT BE MOVED UNITL YAML IS IMPLEMENTED

/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern SDL_Surface *bombSprite;
extern SDL_Surface *bossSprite;
extern SDL_Surface *plyrSprite;
extern SDL_Surface *platformSprite1;
extern SDL_Surface *platformSpriteA1;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
//extern int frameCount;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern SDL_Event event;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern entity_t *enemy1;
extern entity_t *enemy2;
extern entity_t *enemy3;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern entity_t *boss;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern entity_t *wall;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern level_t *stage1;
extern level_t *stage2;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern entity_t *platform1;
extern entity_t *platform2;
extern entity_t *platform3;
extern entity_t *platform4;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern entity_t *platformA1;
extern entity_t *platformA2;
extern entity_t *platformA3;
extern entity_t *platformA4;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern entity_t *lvlTrigger;