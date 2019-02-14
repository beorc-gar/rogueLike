#ifndef _ROGUE_H
#define _ROGUE_H

/*
 playRogue: Allows the user to interact with the game
 Pre: game has been drawn
 Post: game over
*/
void playRogue(hero me,int xDif[],int yDif[],room* rooms,object** monsters);

/*
 addScore: Calculates a score the user acheived and saves it to file
 Pre: user died or beat the game
 Post: return to menu
*/
void addScore(char name[],int gold,int mult);

/*
 newRoom: Moves the user to the closest room
 Pre: user walked into a door
 Post: user is in a new room
*/
void newRoom(hero* me,int moveX,int moveY,int xDif[],int yDif[]);

/*
 endGame: Displays wther user won/lost, and all the items they collected
 Pre: user died or beat the game
 Post: users score is entered to highscore file
*/
void endGame(hero me,int gold,int magic,int weapons,int potions);

/*
 makeBossRoom: Generates a boss room and puts the user in it
 Pre: user walked into stairs
 Post: user can start interacting with the boss room
*/
void makeBossRoom(hero* me,object* boss,object* bonusBoss,object** monsters);

/*
 hitMob: Simulates combat with the nearest monster
 Pre: user waslked into a monster
 Post: damage is taken
*/
void hitMob(hero* me,object* mob,int yDif[],int xDif[]);

/*
 mobMove: Moves the monster(s) in the room one step closer to the hero
 Pre: user moved
 Post: monster(s) is/are closer
*/
void mobMove(hero me,object* mob,int yDif[],int xDif[]);

/*
 showStats: Displays current health, damage, and room
 Pre: user is playing the game
 Post: get user input
*/
void showStats(hero me,int gold,object boss,object bonusBoss);

#endif  //_ROGUE_H_
