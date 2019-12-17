#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include<vector>
#include <stdlib.h>
#include <iostream>
#include "miss.h"
#include "AlienShip.h"
#include "globals.h"
#include "bullets.h"
//constructor 
//	miss(int x, int y, ALLEGRO_BITMAP* pic);
bullet::bullet(int x, int y, ALLEGRO_BITMAP* pic) {
	xpos = x;
	ypos = y;
}


void bullet::move() {
	ypos += 8;
}
void bullet::draw() {
	if (alive == true) {
		//al_draw_bitmap(shipPic, xpos, ypos, NULL);
		al_draw_filled_circle(xpos + 16, ypos + 5, 3, al_map_rgb(255, 0, 0));
	}
}
void bullet::kill() {


	alive = false;
}
bool bullet::offScreen() {
	if (ypos < 0)
		return true;
	else
		return false;
}
bool bullet::isAlive() {
	return alive;
}
void bullet::shoot(int x, int y) {
	alive = true;
	xpos = x;
	ypos = y;
}
bool bullet::collide(double xpos, double ypos) {

	return true;
}


int bullet::getx() {
	return xpos;

}

int bullet::gety() {
	return ypos;

}
