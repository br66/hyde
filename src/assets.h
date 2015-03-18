/* All assets (surfaces, entities, levels, etc */

extern SDL_Surface *screen;	
extern SDL_Rect camera;
extern SDL_Surface *bgSprite;
extern SDL_Surface *bgSprite2;
extern SDL_Surface *message;
extern SDL_Surface *seconds;
extern SDL_Surface *bombSprite;
extern SDL_Surface *bossSprite;
extern SDL_Surface *dot;

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