#ifndef _MENU_H
#define _MENU_H

/*
 Menu: Navigate menu selections to make a choice
 Pre: nothing
 Post: a choice is made for use in an if statement
*/
int menu(void);

/*
 instructions: Prints a wall of text telling the user how to play
 Pre: user selected this from the menu
 Post: return to menu
*/
void instructions(void);

/*
 highScores: Gets the names and scores from a file and orders them in descending order
 Pre: user selected this from the menu
 Post: return to menu
*/
void highScores(void);

#endif  //_MENU_H_
