#ifndef _SETUP_H
#define _SETUP_H

/*
 startGame: Dynamically allocates memory to be used for playing the game
 Pre: user selected this from the menu
 Post: the user can start interacting with the game
*/
void startGame(char* fileName);

/*
 readFile: Reads the input file and makes sure it is valid
 Pre: memory has been allocated for the contents of the file
 Post: the contents form the file is parsed
*/
void readFile(char* fileName,char** lineContents);

/*
 parse: Analyzes the file contents and seperates different space delimited things into arrays
 Pre: the file has been read
 Post: structs are made using these arrays
*/
void parse(char** lineContents,char*** subString);

/*
 getRoom: Creates a struct for a room, given the specifications parsed from file
 Pre: file has been parsed
 Post: The game is drawn using the values from the structs
*/
room getRoom(char* firstString);

/*
 getDoor: Creates a struct for a door, given the specifications parsed from file
 Pre: file has been parsed
 Post: The game is drawn using the values from the structs
*/
door getDoor(char* sub);

/*
 getHero: Creates a struct for a hero, given the specifications parsed from file
 Pre: file has been parsed
 Post: The game is drawn using the values from the structs
*/
hero getHero(char*** subString);

/*
 getObject: Creates a struct for an object, given the specifications parsed from file
 Pre: file has been parsed
 Post: The game is drawn using the values from the structs
*/
object getObject(char* subString);

/*
 createDungeon: Draws the game using values from structs
 Pre: structs have been made using the parsed file
 Post: the user can start interacting with the game
*/
void createDungeon(room* rooms,door** doors,object** objects,hero me);

#endif  //_SETUP_H_
