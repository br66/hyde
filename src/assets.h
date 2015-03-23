/* All assets (surfaces, entities, levels, etc */

#define ENTFLAG_SHOW	0x00000001
#define ENTFLAG_THINK	0x00000002
#define ENT_SOLID		0x00000004

extern SDL_Surface *screen;	
extern SDL_Rect camera;
extern SDL_Surface *bgSprite;
extern SDL_Surface *bgSprite2;
extern SDL_Surface *message;
extern SDL_Surface *seconds;
extern SDL_Surface *bombSprite;
extern SDL_Surface *bossSprite;
extern SDL_Surface *dot;
extern SDL_Surface *platformSprite1;
extern SDL_Surface *platformSpriteA1;
extern SDL_Surface *platformSprite2;
extern SDL_Surface *platformSpriteA2;

extern SDL_Rect health;
extern SDL_Rect anger;

extern TTF_Font *font;

extern SDL_Color textColor;

extern Mix_Music *music;

extern Mix_Chunk *scratch;
extern Mix_Chunk *high;
extern Mix_Chunk *med;
extern Mix_Chunk *low;

extern int frameCount;

extern SDL_Event event;

extern Uint8 *keystates;

extern Uint32 currentTime;
extern Uint32 delta;

extern entity_t *enemy1;
extern entity_t *enemy2;
extern entity_t *enemy3;

extern entity_t *boss;

extern entity_t *wall;

extern entity_t *player;

extern level_t *stage1;
extern level_t *stage2;

extern entity_t *platform1;
extern entity_t *platform2;
extern entity_t *platform3;
extern entity_t *platform4;

extern entity_t *platformA1;
extern entity_t *platformA2;
extern entity_t *platformA3;
extern entity_t *platformA4;

extern entity_t *lvlTrigger;

#define REMOVE_FLAG(x, y) (x &= ~y)
#define SET_FLAG(x, y) (x |= y)
#define IS_SET(x, y) (x & y)