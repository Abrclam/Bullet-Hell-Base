#pragma once
#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include<vector>
#include <stdlib.h>
#include <iostream>
#include "miss.h"
#include "AlienShip.h"
#include "globals.h"
#include"bullets.h"
class bullet {
private:
	double xpos;
	double ypos;
	double angle;
	double rad;
	bool alive;
//	ALLEGRO_BITMAP* shipPic;
public:
	void move();
	void draw();
	void kill();
	bool offScreen();
	bool isAlive();
	int getx();
	int gety();
	void shoot(int x, int y);
	bool collide(double xpos, double ypos);
	bullet(int x, int y, ALLEGRO_BITMAP* pic);
};
