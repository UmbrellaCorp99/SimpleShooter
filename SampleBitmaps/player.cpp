#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"

player::~player()
{
	al_destroy_bitmap(image);
}
player::player(int HEIGHT)
{

	image = al_create_bitmap(64,64);   
	if(!image) {
		exit(1);
	}

	al_set_target_bitmap(image);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_filled_rectangle(0,25,50,39,al_map_rgb(75, 75, 75));
	al_draw_filled_rectangle(25,0,39,64,al_map_rgb(50, 50, 50));
	al_draw_circle(32,32,8,al_map_rgb(0, 0, 0),5);

	al_draw_line(0,32,50,32,al_map_rgb(255, 100, 255),2);
	al_draw_line(32,0,32,64,al_map_rgb(255, 100, 255),2);
	al_draw_filled_triangle(50, 25, 50, 39, 64, 32, al_map_rgb(255, 0, 0));
	al_draw_circle(32,32,16,al_map_rgb(200, 200, 200),5);




	x = 20;
	y = HEIGHT / 2;

	speed = 7;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);

}
void player::DrawPlayer()
{
	al_draw_bitmap(image, x,y, 0);
}
void player::MoveUp(BadGuy bg[], int bgnum)
{
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
void player::MoveDown(int HEIGHT, BadGuy bg[], int bgnum)
{
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
void player::MoveLeft(BadGuy bg[], int bgnum)
{
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
void player::MoveRight(int WIDTH, BadGuy bg[], int bgnum)
{
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