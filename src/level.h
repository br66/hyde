typedef struct level_s
{
	char			*level;
	void			(*start)(struct level_s *level);

	SDL_Surface		*surfaces[20];
}level_t;