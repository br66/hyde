typedef struct level_s
{
	char			level[100];
	void			(*start)(struct level_s *level); //will show level stuff

	SDL_Surface		*surfaces[20];
}level_t;

level_t levels[10];