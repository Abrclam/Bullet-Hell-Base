#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include<vector>
#include <stdlib.h>
#include <iostream>
#include "miss.h"
#include "AlienShip.h"
#include "globals.h"
//constructor 
//	miss(int x, int y, ALLEGRO_BITMAP* pic);
miss::miss(int x, int y, ALLEGRO_BITMAP* pic) {
	xpos = x;
	ypos = y;
}


void miss::move() {
	ypos -= 8;
}
void miss::draw() {
	if (alive == true) {
		//al_draw_bitmap(shipPic, xpos, ypos, NULL);
		al_draw_filled_circle(xpos + 16, ypos + 5, 3, al_map_rgb(255, 0, 0));
	}
}
void miss::kill() {


	alive = false;
}
bool miss::offScreen() {
	if (ypos < 0)
		return true;
	else
		return false;
}
bool miss::isAlive() {

		return alive;

}
void miss::shoot(int x, int y) {
	alive = true;
	xpos = x;
	ypos = y;
}
bool miss::collide(double x, double y) {
	x = x + 50;
	y = y + 50;
	if (sqrt((x-xpos)* (x - xpos) + (y-ypos)*(y - ypos))<100) {
		return true;
		
	}
	else
		return false;
}


int miss::getx() {
	return xpos;

}

int miss::gety() {
	return ypos;

}
