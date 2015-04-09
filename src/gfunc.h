#ifndef _FUNC_
#define _FUNC_

#include <yaml.h> // << SUCCESSFUL YAML IMPLEMENTATION

/* Header file for game functions (loading, clearing, etc.) */
bool init();
bool load_Files();
void CheckLevel();
void clear();
char* FormatTimeString(Uint32 offset);
char* timeString(Uint32 offset);
int level; // <<<< TAKE THIS OUT, PUT IN LEVEL HEADER...

SDL_Rect getCamera (void);
SDL_Rect *addrCamera (void);

TTF_Font *getFont (void);

Uint32 getCurrentTime (void);
void setCurrentTime(void);

SDL_Surface *getSeconds(void);
void setUpSeconds(char* msg, SDL_Color textColor);
void closeSeconds(void);

#endif