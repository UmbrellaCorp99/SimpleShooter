//Alexander Young
//Lab 7

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"

//Deconstructor for the player class
//Takes no parameters
//No return
player::~player()
{
	for (int i = 0; i < 4; i++) {
		al_destroy_bitmap(image[i]);
	}
}

//Constructor for the player class, sets private variables and creates 4 bitmaps
//Takes an integers representing the height of the display as the parameter
//No return
player::player(int HEIGHT)
{
	for (int i = 0; i < 4; i++) {
		image[i] = NULL;
	}

	x = 20;
	y = HEIGHT / 2;
	dir = 1;
	speed = 7;

}

//This function draws a player, dependant on the direction provided
//Takes no parameters
//No return
void player::DrawPlayer()
{
	al_draw_bitmap(image[getDir()], x, y, 0);
}

//This function creates 4 bitmaps
//Takes the display as the parameter
//No return
void player::createImageBM(ALLEGRO_DISPLAY* display) {
	for (int i = 0; i < 4; i++)
	{
		image[i] = al_create_bitmap(64, 64);
		boundx = al_get_bitmap_width(image[i]);
		boundy = al_get_bitmap_height(image[i]);
		if (!image[i]) {
			exit(1);

		}

		al_set_target_bitmap(image[i]);
		al_clear_to_color(al_map_rgb(0, 0, 0));

		//changed x and y values to 32 since I am using a 64x64 bitmap
		int x = 32;
		int y = 32;

		//Added my own bitmap for each case
		switch (i)
		{
		case 0: //Up
			al_draw_filled_triangle(27, 32, 37, 32, 32, 0, al_map_rgb(255, 255, 0));
			al_draw_filled_circle(x, y, 17, al_map_rgb(0, 0, 255));
			al_draw_circle(x + 5, y - 8, 5, al_map_rgb(0, 0, 0), 2);
			al_draw_filled_rectangle(x + 3, y - 11, x + 8, y - 5, al_map_rgb(255, 0, 0));
			break;
		case 1://Right
			al_draw_filled_triangle(32, 27, 32, 37, 64, 32, al_map_rgb(255, 255, 0));
			al_draw_filled_circle(x, y, 17, al_map_rgb(0, 0, 255));
			al_draw_circle(x + 8, y - 5, 5, al_map_rgb(0, 0, 0), 2);
			al_draw_filled_rectangle(x + 6, y - 8, x + 11, y - 2, al_map_rgb(255, 0, 0));
			break;
		case 2://Down
			al_draw_filled_triangle(27, 32, 37, 32, 32, 64, al_map_rgb(255, 255, 0));
			al_draw_filled_circle(x, y, 17, al_map_rgb(0, 0, 255));
			al_draw_circle(x + 5, y + 8, 5, al_map_rgb(0, 0, 0), 2);
			al_draw_filled_rectangle(x + 3, y + 11, x + 8, y + 5, al_map_rgb(255, 0, 0));
			break;
		case 3: //Left
			al_draw_filled_triangle(32, 27, 32, 37, 0, 32, al_map_rgb(255, 255, 0));
			al_draw_filled_circle(x, y, 17, al_map_rgb(0, 0, 255));
			al_draw_circle(x - 8, y - 5, 5, al_map_rgb(0, 0, 0), 2);
			al_draw_filled_rectangle(x - 6, y - 8, x - 11, y - 2, al_map_rgb(255, 0, 0));
			break;
		}
	}
}

//This function moves the character up and sets the dir variable to allow for the bitmap to face up. Collision detection with BadGuys included
//Takes a BadGuy object and and integer representing the number of BadGuys as parameters
//No return
void player::MoveUp(BadGuy bg[], int bgnum)
{
	dir = 0;
	y -= speed;
	if (y < 0) {
		y = 0;
	}
	for (int j = 0; j < bgnum; j++)
	{
		if (bg[j].getLive())
		{
			if (((x > bg[j].getX()) && x < (bg[j].getX() + bg[j].getBoundX()) ||
				(((x + boundx) > bg[j].getX()) && ((x + boundx) < (bg[j].getX() + bg[j].getBoundX())))) &&
				(y > bg[j].getY()) && (y < (bg[j].getY() + bg[j].getBoundY())))
			{
				y = (bg[j].getY() + bg[j].getBoundY());
			}
		}
	}
}

//This function moves the character down and sets the dir variable to allow for the bitmap to face down. Collision detection with BadGuys included
//Takes a BadGuy object and and integer representing the number of BadGuys as parameters
//No return
void player::MoveDown(int HEIGHT, BadGuy bg[], int bgnum)
{
	dir = 2;
	y += speed;
	if (y > HEIGHT - boundy) {
		y = HEIGHT-boundy;
	}
	for (int j = 0; j < bgnum; j++)
	{
		if (bg[j].getLive())
		{
			if (((x > bg[j].getX()) && x < (bg[j].getX() + bg[j].getBoundX()) ||
				(((x + boundx) > bg[j].getX()) && ((x + boundx) < (bg[j].getX() + bg[j].getBoundX())))) &&
				(y < (bg[j].getY())) && ((y + boundy) > (bg[j].getY())))
			{
				y = (bg[j].getY() - boundy);
			}
		}
	}
}
//This function moves the character left and sets the dir variable to allow for the bitmap to face left. Collision detection with BadGuys included
//Takes a BadGuy object and and integer representing the number of BadGuys as parameters
//No return

void player::MoveLeft(BadGuy bg[], int bgnum)
{
	dir = 3;
	x -= speed;
	if (x < 0) {
		x = 0;
	}
	for (int j = 0; j < bgnum; j++)
	{
		if (bg[j].getLive())
		{
			if (((y > bg[j].getY()) && y < (bg[j].getY() + bg[j].getBoundY()) || 
				(((y + boundy) > bg[j].getY()) && ((y + boundy) < (bg[j].getY() + bg[j].getBoundY())))) &&
				(x > (bg[j].getX())) && (x < (bg[j].getX() + bg[j].getBoundX())))
			{
				x = (bg[j].getX() + bg[j].getBoundX());
			}
		}
	}
}

//This function moves the character right and sets the dir variable to allow for the bitmap to face right. Collision detection with BadGuys included
//Takes a BadGuy object and and integer representing the number of BadGuys as parameters
//No return
void player::MoveRight(int WIDTH, BadGuy bg[], int bgnum)
{
	dir = 1;
	x += speed;
	if (x > WIDTH - boundx) {
		x = WIDTH - boundx;
	}
	for (int j = 0; j < bgnum; j++)
	{
		if (bg[j].getLive())
		{
			if (((y > bg[j].getY()) && y < (bg[j].getY() + bg[j].getBoundY()) ||
				(((y + boundy) > bg[j].getY()) && ((y + boundy) < (bg[j].getY() + bg[j].getBoundY())))) &&
				(x < bg[j].getX()) && ((x + boundx) > (bg[j].getX())))
			{
				x = (bg[j].getX() - boundx);
			}
		}
	}
}