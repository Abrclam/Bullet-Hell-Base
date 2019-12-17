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
//constants: variables that shouldn't change once the game starts
const float FPS = 60;
const int SCREEN_W = 1000;
const int SCREEN_H = 1000;
//enumeration to help you remember what numbers represent which directions
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};
enum DIRECTIONS {
	UP, DOWN, LEFT, RIGHT

};
