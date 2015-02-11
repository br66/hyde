//OH NO C DOESN'T HAVE THE CONCPET OF DATA HIDING!
//Y? C Y?
//FUNCTION POINTERS

//CHANGED INCLUDE DIRECTORIES



typedef struct objTest_s
{
	int x, y;
	int xVel, yVel;

	void (*handleInput) (struct objTest_s *self);
	//void (*move) (objTest_t *self);
	//void (*show) (objTest_t *self);

} objTest_t; //created an entiity type for entity


