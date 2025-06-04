//Alexander Young
//Lab 7

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"
#include "BadGuy.h"
#include "weapon.h"





int main(void)
{

	//variables used within the main function
	const int WIDTH = 800;
	const int HEIGHT = 400;
	const int NUM_weapons = 5;
	const int NUM_BadGuyS = 5;
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
	bool keys[5] = {false, false, false, false, false};

	//primitive variable
	bool done = false;
	bool redraw = true;
	const int FPS = 60;


	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	//Initialization Functions
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;
	
	//initializing the privitives, keyboard, and image addons
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();


	//object variables
	player myPlayer(HEIGHT);
	weapon weapons[NUM_weapons];
	BadGuy BadGuys[NUM_BadGuyS];

	//creating player bitmap, event queue, and timer
	myPlayer.createImageBM(display);
	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	srand(time(NULL));

	//tyring keyboard, timer, and display into event queue
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	//pulling the bitmap to the front buffer
	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	myPlayer.DrawPlayer();
	al_flip_display();
	al_start_timer(timer);
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//If the event queue gets a timer event
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			//Move the player if the direction keys were pressed
			redraw = true;
			if(keys[UP])
				myPlayer.MoveUp(BadGuys, NUM_BadGuyS);
			if(keys[DOWN])
				myPlayer.MoveDown(HEIGHT, BadGuys, NUM_BadGuyS);
			if(keys[LEFT])
				myPlayer.MoveLeft(BadGuys, NUM_BadGuyS);
			if(keys[RIGHT])
				myPlayer.MoveRight(WIDTH, BadGuys, NUM_BadGuyS);
			//update the status of weapons and bad guys on the display
			for(int i=0;i<NUM_weapons;i++)
				weapons[i].Updateweapon(WIDTH, HEIGHT);
			for(int i=0;i<NUM_BadGuyS;i++)
				BadGuys[i].StartBadGuy(WIDTH,HEIGHT, BadGuys, NUM_BadGuyS);
			for(int i=0;i<NUM_weapons;i++)
				weapons[i].Collideweapon(BadGuys, NUM_BadGuyS);

		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			//store the following keyboard inputs for parsing during the next loop
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
				//if space is pressed, fire the weapon
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				for(int i=0;i<NUM_weapons;i++)
					weapons[i].Fireweapon(myPlayer);
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		//after every game loop, draw new bad guys and weapons if needed 
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false; 

			myPlayer.DrawPlayer();
			for(int i=0;i<NUM_weapons;i++)
				weapons[i].Drawweapon();
			for(int i=0;i<NUM_BadGuyS;i++)
				BadGuys[i].DrawBadGuy();

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	//destroy the following pointers from memory
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}





