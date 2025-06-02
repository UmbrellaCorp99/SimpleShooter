#ifndef PLAYERH
#define PLAYERH
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "BadGuy.h"

class player
{
public:
	player(int HEIGHT);
	~player();
	void DrawPlayer();
	void MoveUp(BadGuy bg[], int bgnum);
	void MoveDown(int HEIGHT, BadGuy bg[], int bgnum);
	void MoveLeft(BadGuy bg[], int bgnum);
	void MoveRight(int WIDTH, BadGuy bg[], int bgnum);
	int getBoundX(){return boundx;}
	int getBoundY(){return boundy;}
	int getX(){return x;}
	int getY(){return y;}
private:
	int x;
	int y;
	int speed;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP *image;
};
#endif

