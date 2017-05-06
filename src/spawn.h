#ifndef _SPAWN_
#define _SPAWN_

// level editor eh?

/* new header for spawning instances of entities */
//void spawnPlayer(float x, float y); // spawn player at certain position
void spawnEntity(const char * name, float x, float y, const char * flag); // spawn entity at certain position, check name to determine which entity to spawn
//void enemySpawner (const char * name, float x, float y); // will spawn multiple enemies depending on player's mode
void spawnParticle (int x, int y, float speed);
void spawnMultiParticle (int x, int y, float speed);
 
#endif