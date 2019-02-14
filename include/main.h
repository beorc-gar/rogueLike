#ifndef _MAIN_H
#define _MAIN_H

#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

typedef struct hero {
    int xPos;
    int yPos;
    int health;
    int damage;
    int start;
}hero;

typedef struct door {
    char wall;
    int tile;
}door;

typedef struct object {
    int xPos;
    int yPos;
    int health;
    int speed;
    int damage;
    int start;
    int colour;
    char icon;
}object;

typedef struct room {
    int height;
    int width;
}room;

#endif  // INCLUDE_MAIN_H_
