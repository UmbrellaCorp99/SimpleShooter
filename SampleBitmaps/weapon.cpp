#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "weapon.h"

//This is a deconstructor for the weapon class
//Takes no parameters
//No return
weapon::~weapon()
{
	al_destroy_bitmap(image);
}

//This is a constructor for the weapon class. It creates a bitmap for the weapon and sets the private variables
//Takes no parameters
//No return
weapon::weapon()
{
	speed = 10;
	live = false;
	image = al_create_bitmap(64,64);   
	if(!image) {
		exit(1);
	}

	al_set_target_bitmap(image);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(0,25,64,39,al_map_rgb(0, 255, 255));
	al_draw_filled_rectangle(25,0,39,64,al_map_rgb(0, 255, 255));		
	al_draw_circle(32,32,8,al_map_rgb(100, 100, 100),5);

	al_draw_line(0,32,64,32,al_map_rgb(100, 100, 255),2);
	al_draw_line(32,0,32,64,al_map_rgb(100, 100, 255),2);
	al_draw_circle(32,32,16,al_map_rgb(200, 200, 200),5);
	x = 0;
	y = 0;


	speed = 7;
	boundx = al_get_bitmap_width(image)/2;
	boundy = al_get_bitmap_height(image)/2;
	live=false;
	angle=0;
	dir = 0;
}

//This function draws the weapon. Every time it is drawn, it rotates by .1 degrees
//Takes no parameters
//No return
void weapon::Drawweapon()
{

	if(live){
		al_draw_scaled_rotated_bitmap(image,32,32,x,y,.5,.5,angle,0);
		angle+=.1;
	}
}

//This function fires the weapon in the direction that the player is facing from the appropriate location
//Takes a player object as a parameter
//No return
void weapon::Fireweapon( player &Player)
{
	if(!live)
	{	
		dir = Player.getDir();
		switch (dir) {
		case 0:
			x = Player.getX() + Player.getBoundX()/2;
			y = Player.getY();
			break;
		case 1:
			x = Player.getX() + Player.getBoundX();
			y = Player.getY() + Player.getBoundY() / 2;
			break;
		case 2:
			x = Player.getX() + Player.getBoundX() / 2;
			y = Player.getY() + Player.getBoundY();
			break;
		case 3:
			x = Player.getX();
			y = Player.getY() + Player.getBoundY() / 2;
			break;
		}
		
		live = true;
	}
}

//This function updates the location of the weapon after being fired, dependant on the location the player was facing when it was fired
//Takes two integers representing the height and width of the display
//No return
void weapon::Updateweapon(int WIDTH, int HEIGHT)
{
	if(live)
	{
		switch (dir) {
		case 0:
			y -= speed;
			if (y < 0)
			live = false;
			break;
		case 1:
			x += speed;
			if (x > WIDTH)
			live = false;
			break;
		case 2:
			y += speed;
			if (y > HEIGHT)
				live = false;
			break;
		case 3:
			x -= speed;
			if (x < 0)
				live = false;
			break;
		}
	}
}

//This function changes the status of a BadGuy and the weapon upon collision with the weapon
//Takes BadGuy objects and and int representing the number of BadGuys as parameters
//No return
void weapon::Collideweapon(BadGuy BadGuys[], int cSize)
{
	if(live)
	{
		for(int j =0; j < cSize; j++)
		{
			if(BadGuys[j].getLive())
			{
				if(x > (BadGuys[j].getX() - BadGuys[j].getBoundX()) &&
					x < (BadGuys[j].getX() + BadGuys[j].getBoundX()) &&
					y > (BadGuys[j].getY() - BadGuys[j].getBoundY()) &&
					y < (BadGuys[j].getY() + BadGuys[j].getBoundY()))
				{
					live = false;
					BadGuys[j].setLive(false);
				}
			}
		}
	}

}

