
#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include<vector>
#include <stdlib.h>
#include <iostream>
#include "miss.h"
#include "AlienShip.h"
#include "globals.h"
void AlienShip::move() {
	//right movement
	if (xdir == 1) //1 means right
		xpos += 1;
	if (xdir == 1 && xpos > 800) //you can replace screen_w with the width of your screen
		xdir = 0; //0 means left

		//left movement
	if (xdir == 0) //move left
		xpos -= 1;
	if (xdir == 0 && xpos < 0) //you can replace screen_w with the width of your screen
		xdir = 1; //move right again

	if (ydir == 2)
		ypos += 1.1;
	if (ydir == 2 && ypos > 400)
		ydir = 0;

	if (ydir == 0)
		ypos -= 1.1;
	if (ydir == 0 && ypos < 0)
		ydir = 2;
}
void AlienShip::draw() {
	al_draw_bitmap(mothership, xpos, ypos, NULL);

}

void AlienShip::decreaseHealth() {
	health -= .1;
}
int AlienShip::getY() { return ypos; }
int AlienShip::getX() { return xpos; }
int AlienShip::getHealth() { return health; }
AlienShip::AlienShip(int x, int y, ALLEGRO_BITMAP* pic) {
	/*The constructor sets the xand y positions, the xdirand ydir to 0 and 2, and the image to pic.
	The draw function just calls al_draw_bitmap.*/
	xpos = x;
	ypos = y;
	mothership = pic;
	xdir = 0;
	ydir = 2;
	health = 100;
} //constructor
