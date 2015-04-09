/* For this commit, getCamera() returns camera to lessen externs.
addrCamera() gets the address of the camera for surface blitting.
getFont() gets the font and getCurrentTime() returns camera to
lessen externs.  setCurrentTime() sets the currentTime variable
to SDL_GetTicks() which gets the raw time and replaces a line in
game.c and lessens externs. */

#ifndef _FUNC_
#define _FUNC_

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

#endif