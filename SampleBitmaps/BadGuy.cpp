//Alexander Young
//Lab 7

#include "BadGuy.h"

//Deconstructor for the BadGuy class
//Takes no parameters
//No return
BadGuy::~BadGuy()
{
	al_destroy_bitmap(image);
}

//Constructor for the BadGuy class, creates a bitmap and sets private variables
//Takes no parameters
//No return
BadGuy::BadGuy()
{
	image = al_create_bitmap(64,64);   
	if(!image) {
		exit(1);
	}

	al_set_target_bitmap(image);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	x = 0;
	y = 0;

	al_draw_filled_rectangle(25,10,39,54,al_map_rgb(100, 100, 120));
	al_draw_filled_ellipse(32,32,32,16,al_map_rgb(255, 0, 255));
	al_draw_filled_circle(32,32,4,al_map_rgb(255, 255, 255));
	al_draw_filled_circle(16,32,4,al_map_rgb(120, 255, 255));
	al_draw_filled_circle(48,32,4,al_map_rgb(255, 255, 120));
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	live = false;

}

//Draws a BadGuy bitmap at the provided x and y location
//Takes no parameters
//No return
void BadGuy::DrawBadGuy()
{
	if(live)
	{
		al_draw_bitmap(image,x,y,0);
	}
}

//This function generates a random x and y location for a BadGuy to spawn at, ensuring no overlap
//Takes two integers representing the display's height and width, BadGuy objects, and and int representing the number of BadGuys as parameters
//No return
void BadGuy::StartBadGuy(int WIDTH, int HEIGHT, BadGuy bg[], int bgnum)
{
	if (!live)
	{
		if (rand() % 500 == 0)
		{
			live = true;
			bool collision;
			const int buffer = 64; //buffer distance this relates to how big your bitmap is

			do {
				collision = false;
				x = rand() % (WIDTH - boundx);
				y = rand() % (HEIGHT - boundy);

				// Check for collision with other bad guys
				for (int i = 0; i < bgnum; i++)
				{
					if (bg[i].getLive() && &bg[i] != this)
					{
						// buffer in collision check
						if (x > (bg[i].getX() - bg[i].getBoundX() - buffer) && x < (bg[i].getX() + bg[i].getBoundX() + buffer) &&
							y >(bg[i].getY() - bg[i].getBoundY() - buffer) && y < (bg[i].getY() + bg[i].getBoundY() + buffer))
						{
							collision = true;
							break;
						}
					}
				}
			} while (collision);
		}
	}
}

