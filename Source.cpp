#include <allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include<allegro5\allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<vector>
#include <stdlib.h>
#include <iostream>
#include "miss.h"
#include "AlienShip.h"
#include "bullets.h"
#include "globals.h"
using namespace std;


int v1 = rand() % 255+1;
int v2 = rand() % 255+1;
int v3 = rand() % 255+1;
int AlienHit = 0;
int hitX = 0;
int hitY = 0;




int main()
{
	//set up allegro
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();
	srand(time(NULL));
	al_init_font_addon();
	al_init_ttf_addon();


	//set up game screen, event queue, and timer
	
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_BITMAP* shipPic = al_load_bitmap("ship.png");
	ALLEGRO_BITMAP* cat = al_load_bitmap("mothership.png");
	ALLEGRO_BITMAP* dinopic = al_load_bitmap("dino.jpg");

	al_convert_mask_to_alpha(cat, al_map_rgb(255, 255, 255));
	ALLEGRO_BITMAP* explosion = al_load_bitmap("explosion.png");
	al_convert_mask_to_alpha(explosion, al_map_rgb(255, 255, 255));
	ALLEGRO_FONT* font=al_load_font("sponge.ttf",25,0);
	//if (font == NULL) cout << "derp" << endl;
	//instantiate two alien ships
	AlienShip Mothership(400, 300, cat);
	AlienShip Mothership2(100, 100, cat);

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);

	al_start_timer(timer);

	//position of player
	double xPos = 400;
	double yPos = 700;
	int ticker = 0;
	int cellNum = 0;
	int dir = 0;
	//game variables
	bool key[5] = { false, false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop
	int justShot = 0;
	int curFrame=0;
	int frameWidth;
	int frameHeight;
	int playerHealth = 100;
	//tell event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//vector to hold missiles
	vector<miss*>misses;
	vector<miss*>::iterator iter2;
	for (int i = 0; i < 5; i++) {
		miss* newMissile = new miss(0, 0, shipPic);
		misses.push_back(newMissile);
	}

	//intro screen!///////////////////////////////////////////////////////////////////////////////
	for (float i = 0; i < 1; i += .0005) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	//fade in
	for (float i = 0; i < 1; i += .0008) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_tinted_bitmap(dinopic, al_map_rgba_f(1, 1, 1, i), 50, 50, 0);
		al_flip_display();
	}
	//stay solid for a second
	for (float i = 0; i < 1; i += .001) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_tinted_bitmap(dinopic, al_map_rgba_f(1, 1, 1, 1), 50, 50, 0);
		al_flip_display();
	}
	//fade out
	for (float i = 1; i > 0; i -= .0005) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_tinted_bitmap(dinopic, al_map_rgba_f(i, 1, 1, i), 50, 50, 0);
		al_flip_display();
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////

	while (!doexit)//game loop!
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		
		
		//timer (physics) section////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (Mothership.getHealth() <= 0 && Mothership2.getHealth() <= 0)
				doexit = true;
			Mothership.move();
			Mothership2.move();
			for (iter2 = misses.begin(); iter2 != misses.end(); iter2++) {
				if ((*iter2)->collide(Mothership.getX(), Mothership.getY())) {
					if(Mothership.getHealth()>0)
					Mothership.decreaseHealth();
					//cout << "Mothership hit! " << endl;
					AlienHit = 30;
					hitX = (*iter2)->getx();
					hitY = (*iter2)->gety();
					(*iter2)->kill();
				}

			}
			for (iter2 = misses.begin(); iter2 != misses.end(); iter2++) {
				if ((*iter2)->collide(Mothership2.getX(), Mothership2.getY())) {
					if (Mothership2.getHealth() > 0)
					Mothership2.decreaseHealth();
					//cout << "Mothership hit! " << endl;
					AlienHit = 30;
					hitX = (*iter2)->getx();
					hitY = (*iter2)->gety();
					(*iter2)->kill();

				
				}

			}
			//slows down animation
			ticker++;
			if (ticker > 10)
				ticker = 0;
			justShot++;
			if (ticker == 0)
				cellNum++;
			if (cellNum > 4)
				cellNum = 0;
			//move missiles
			for (iter2 = misses.begin(); iter2 != misses.end(); iter2++) {
				if ((*iter2)->isAlive())
					(*iter2)->move();
			}
			//cull missiles
			for (iter2 = misses.begin(); iter2 != misses.end(); iter2++) {
				if ((*iter2)->offScreen())
					(*iter2)->kill();
			}


			//move animation forward, loop after 4 cells
			if (dir == UP || dir == DOWN) {
				if (cellNum > 4)
					cellNum = 0;
			}
			if (dir == LEFT || dir == RIGHT) {
				if (cellNum < 5)
					cellNum = 5;
				if (cellNum > 9)
					cellNum = 5;
			}
			if (key[KEY_RIGHT])
				dir = RIGHT;
			else if (key[KEY_LEFT])
				dir = LEFT;
			else
				dir = UP;
			//move player 4 pixels in a direction when key is pressed
			if (key[KEY_UP]) {
				yPos -= 4.0;

			}

			if (key[KEY_DOWN]) {
				yPos += 4.0;

			}

			if (key[KEY_LEFT]) {
				xPos -= 4.0;

			}

			if (key[KEY_RIGHT]) {
				xPos += 4.0;

			}

			if (key[KEY_SPACE]) {
				for (iter2 = misses.begin(); iter2 != misses.end(); iter2++) {
					if (((*iter2)->isAlive()) == false && justShot > 10) {
						(*iter2)->shoot(xPos, yPos);
						justShot = 0;
					}

				}


			}

			redraw = true;
		}

		//keyboard and screen sections//////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		//render section//////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			
			
			
			
			
		
			
			
			
			//al_draw_filled_rounded_rectangle()

			if (AlienHit > 0) {

				//al_draw_bitmap_region(explosion, curFrame* 32, 0, 32,32, hitX, hitY, 0);
				al_draw_filled_circle(hitX, hitY, 20, al_map_rgb(255, 0, 0));
				al_draw_filled_circle(hitX, hitY, 10, al_map_rgb(195, 0, 0));
				AlienHit--;
			}
			
			
			Mothership.draw();
			
			
			Mothership2.draw();
			
			
			for (iter2 = misses.begin(); iter2 != misses.end(); iter2++) {
				(*iter2)->draw();
			}

			al_draw_bitmap_region(shipPic, cellNum * 32, 0, 32, 32, xPos, yPos, NULL);
			if (dir == LEFT)
				al_draw_bitmap_region(shipPic, cellNum * 32, 0, 32, 32, xPos, yPos, ALLEGRO_FLIP_HORIZONTAL);
			else
				al_draw_bitmap_region(shipPic, cellNum * 32, 0, 32, 32, xPos, yPos, NULL);
			
			//draw player health
			al_draw_rectangle(20, 20, 120, 40, al_map_rgb(255, 255, 255), 5);
			al_draw_filled_rectangle(20, 20, 20 + playerHealth, 40, al_map_rgb(255, 40, 0));
			al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 55, NULL, "Player Health");
			
			//draw mothership health
			al_draw_rectangle(400, 20, 500, 40, al_map_rgb(255, 255, 255), 5);
			al_draw_filled_rectangle(400, 20, 400 + Mothership.getHealth(),40, al_map_rgb(200, 40, 140));
			al_draw_textf(font, al_map_rgb(255, 255, 255), 390, 55, NULL, "Enemy Health");
			al_draw_rectangle(690, 20, 790, 40, al_map_rgb(255, 255, 255), 5);
			al_draw_filled_rectangle(690, 20, 690 + Mothership2.getHealth(), 40, al_map_rgb(200, 40, 140));
			al_draw_textf(font, al_map_rgb(255, 255, 255), 690, 55, NULL, "Enemy 2 Health");
			
			
			al_flip_display(); //flip everything from memory to gamescreen

		}//end render

		
	}//end game loop

	
	//clean up memory
	al_destroy_bitmap(dinopic);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
