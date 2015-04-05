/* 
GAME STRUCTURE
Game.getScreen();
Game.getCamera();
Game.getSprite(); ????
Game.getHealth(); ???
Game.getAnger(); ???
Game.setHealth(); ???
Game.setAnger(); ???
Game.getTime(); ???
Game.setTime(); ???
Game.getPlayer();
Game.start();
Game.end();
Game.running();
Game.loadAssets(); ???
Game.unloadAssets(); ???
Game.getLevel(); ???
Game.setLevel(); ???
Game.getMaxEnts(); ???
Game.setMaxEnts(); ???
Game.init();
*/

typedef struct
{
	void (*getScreen) (void);
	void (*getCamera) (void);
	void (*getPlayer) (void);
} game_t;