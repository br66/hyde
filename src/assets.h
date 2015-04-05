/* All assets (surfaces, entities, levels, etc */
/* NOOOOOOOOOOOO USE GET FUNCTIONS TO RETURN DATA */

#define ENT_SHOW	0x00000001
#define ENT_THINK	0x00000002
#define ENT_SOLID	0x00000004

/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern SDL_Surface *screen;	// getScreen void function // global header // line 27
extern SDL_Rect camera;
extern SDL_Surface *bgSprite;
extern SDL_Surface *bgSprite2;
extern SDL_Surface *message;
extern SDL_Surface *seconds;
extern SDL_Surface *bombSprite;
extern SDL_Surface *bossSprite;
extern SDL_Surface *plyrSprite;
extern SDL_Surface *platformSprite1;
extern SDL_Surface *platformSpriteA1;
extern SDL_Surface *platformSprite2;
extern SDL_Surface *platformSpriteA2;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern SDL_Rect health;
extern SDL_Rect anger;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern TTF_Font *font;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern SDL_Color textColor;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern Mix_Music *music;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern Mix_Chunk *scratch;
extern Mix_Chunk *high;
extern Mix_Chunk *med;
extern Mix_Chunk *low;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern int frameCount;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern SDL_Event event;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern Uint8 *keystates;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern Uint32 currentTime;
extern Uint32 delta;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern entity_t *enemy1;
extern entity_t *enemy2;
extern entity_t *enemy3;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern entity_t *boss;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern entity_t *wall;
/* FUNCTIONS MUST BE TRANSFERRED TO GET FUNCTIONS */
extern entity_t *player;
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

#define REMOVE_FLAG(x, y) (x &= ~y)
#define SET_FLAG(x, y) (x |= y)
#define IS_SET(x, y) (x & y)