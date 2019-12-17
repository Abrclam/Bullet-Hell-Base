#pragma once
#include<allegro5/allegro.h>
#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include<vector>
#include <stdlib.h>
#include <iostream>
#include "miss.h"
#include "AlienShip.h"
#include "globals.h"
class AlienShip {
private:
	double xpos;
	double ypos;
	double xdir;
	double ydir;
	int health;
	ALLEGRO_BITMAP* mothership;
public:
	void move();
	void draw();
	void decreaseHealth();
	int getY();
	int getX();
	int getHealth();
	AlienShip(int x, int y, ALLEGRO_BITMAP* pic); //constructor

};
