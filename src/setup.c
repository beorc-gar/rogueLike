/*******************************setup.c*****************************************************
Student Name: Bronson Graansma                Student Number: 0872249
Date:         Monday, March 2nd, 2015         Course Name:    CIS*2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
*********************************************************************************************/

#include "main.h"
#include "menu.h"
#include "setup.h"
#include "rogue.h"

void startGame(char* fileName) {
    int i = 0;
    int j = 0;
    room* rooms = malloc(sizeof(room)*6);
    door** doors = malloc(sizeof(door*)*6);
    object** objects = malloc(sizeof(object*)*6);
    hero bronson;
    char*** subString = malloc(sizeof(char**)*6);
    char** lineContents = malloc(sizeof(char*)*6);
    
    for (i=0; i<6; i++) {
        doors[i] = malloc(sizeof(door)*50);
        objects[i] = malloc(sizeof(object)*50);
        lineContents[i] = malloc(sizeof(char)*150);
        subString[i] = malloc(sizeof(char*)*50);
        for (j=0; j<50; j++) {
            subString[i][j] = malloc(sizeof(char)*7);
        }
    }

    readFile(fileName,lineContents);
    parse(lineContents,subString);
    bronson = getHero(subString);

    for (i=0; i<6; i++) {
        rooms[i] = getRoom(subString[i][0]);
        
        for (j=0; j<50; j++) {
            doors[i][j] = getDoor(subString[i][j]);
            objects[i][j] = getObject(subString[i][j]);
        }
    }
    createDungeon(rooms, doors, objects, bronson);

    for (i=0; i<6; i++) {
        free(lineContents[i]);
        free(objects[i]);
        free(doors[i]);
        
        for (j=0; j<50; j++) {
            free(subString[i][j]);
        }
        free(subString[i]);
    }
    free(lineContents);
    free(subString);
    free(objects);
    free(rooms);
    free(doors);

    return;
}

void readFile(char* fileName,char** lineContents) {
    FILE* filePtr;
    int i = 0;
    int j = 0;
    int k = 0;
    int badFiles = 0;

    while ((filePtr = fopen(fileName,"r"))==NULL && badFiles<2) {
        endwin();
        printf("Can't open <%s>. Using default level instead.\n",fileName);
        initscr();
        start_color();
        sprintf(fileName,"assets/default.txt");
        badFiles++;
    }
    
    if (badFiles==2) {
        endwin();
        printf("Default file corrupt or missing.");
        exit(1);
    }

    for (i=0; i<6; i++) {
        fgets(lineContents[i],150,filePtr);
    }
    fclose(filePtr);

    for (i=0; i<6; i++) {
        for (j=0; j<150; j++) {
            if (lineContents[i][j] == '.' && lineContents[i][j+1] == '.') {
                for (k=j; k<150; k++) {
                    lineContents[i][k] = lineContents[i][k+1];
                }
            }
            
            if (lineContents[i][j] == '\n' || j==149) {
                lineContents[i][j] = '\0';
                break;
            }
        }
    }

    return;
}

void parse(char** lineContents,char*** subString) {
    int i = 0;
    int j = 0;
    char* token;

    for (i=0; i<6; i++) {
        token = strtok(lineContents[i]," ");
        j = 0;
        
        while (token!=NULL) {
            sprintf(subString[i][j],"%s",token);
            token = strtok(NULL," ");
            j++;
        }
    }

    return;
}

room getRoom(char* firstString) {
    room initRoom;
    int i = 0;
    int dimensions[2] = {0,0};
    char* token = strtok(firstString,"X");

    while (token!=NULL && i<2) {
        dimensions[i] = atol(token) + 2;
        token = strtok(NULL,"X");
        i++;
    }
    initRoom.height = dimensions[0];
    initRoom.width  = dimensions[1];

    return initRoom;
}

door getDoor(char* sub) {
    door initDoor;

    initDoor.wall = 'z';
    initDoor.tile = -1;

    if (sub[0]=='d') {
        sub[0] = ' ';
        
        if (sub[1]=='n' || sub[1]=='e' || sub[1]=='s' || sub[1]=='w') {
            initDoor.wall = sub[1];
            sub[1] = ' ';
            initDoor.tile = atol(sub) + 1;
        }
    }

    return initDoor;
}

hero getHero(char*** subString) {
    int i = 0;
    int j = 0;
    hero initHero;
    char* token;

    initHero.xPos = 1;
    initHero.yPos = 1;
    initHero.health = 100;
    initHero.damage = 15;

    for (i=0; i<6; i++) {
        for (j=0; j<50; j++) {
            if (subString[i][j][0]=='h') {
                subString[i][j][0] = ' ';
                initHero.start = i;
                token = strtok(subString[i][j],",");
                
                if (token!=NULL) {
                    initHero.yPos = atol(token) + 1;
                    token = strtok(NULL,",");
                    
                    if (token!=NULL) {
                        initHero.xPos = atol(token) + 1;
                    }
                }
            }
        }
    }

    return initHero;
}

object getObject(char* subString) {
    object initObject;
    char* token;
    char first = tolower(subString[0]);

    initObject.xPos = -1;
    initObject.yPos = -1;
    initObject.damage = -1;
    initObject.health = -1;
    initObject.icon = 'z';

    if (first=='g' || first=='m' || first=='p' || first=='s' || first=='w') {
        
        switch (subString[0]) {
          case 'g':
            initObject.colour = 3;
            initObject.icon = '*';
            break;

          case 'm':
            initObject.colour = 5;
            initObject.icon = '$';
            break;

          case 'p':
            initObject.colour = 2;
            initObject.icon = '!';
            break;

          case 's':
            initObject.colour = 4;
            initObject.icon = '%';
            break;

          case 'w':
            initObject.colour = 6;
            initObject.icon = ')';
            break;
        }
        
        if (subString[0]=='M') {
            initObject.damage = 15;
            initObject.health = 100;
            initObject.colour = 1;
            initObject.icon = 'M';
        } else {
            initObject.damage = 0;
            initObject.health = 0;
        }
        subString[0] = ' ';
        token = strtok(subString,",");
        
        if (token!=NULL) {
            initObject.yPos = atol(token) + 1;
            token = strtok(NULL,",");
            
            if (token!=NULL) {
                initObject.xPos = atol(token) + 1;
            }
        }
    }

    return initObject;
}

void createDungeon(room* rooms,door** doors,object** objects,hero bronson) {
    int i = 0;
    int j = 0;
    int k = 0;
    int vDif = 0;
    int xDif[6] = {0,0,0,0,0,0};
    int yDif[6] = {1,1,1,0,0,0};

    for (i=0; i<3; i++) {
        if (rooms[i].height > vDif) {
            vDif = rooms[i].height + 1;
        }
    }
    
    for (i=3; i<6; i++) {
        yDif[i] = vDif + 1;
    }
    xDif[1] = rooms[0].width + 2;
    xDif[2] = xDif[1] + rooms[1].width + 2;
    xDif[4] = rooms[3].width + 2;
    xDif[5] = xDif[4] + rooms[4].width + 2;

    for (i=0; i<6; i++) {
        attron(COLOR_PAIR(4));
        
        for (j=0; j<rooms[i].height; j++) {
            mvaddch(j+yDif[i],xDif[i],'|');
            mvaddch(j+yDif[i]+1,rooms[i].width+xDif[i],'|');
        }
        
        for (j=0; j<rooms[i].width+1; j++) {
            mvaddch(yDif[i],j+xDif[i],'-');
            mvaddch(rooms[i].height+yDif[i],j+xDif[i],'-');
        }
        attron(COLOR_PAIR(7));

        for (j=1; j<rooms[i].height; j++) {
            for (k=1; k<rooms[i].width; k++) {
                mvaddch(j+yDif[i],k+xDif[i],'.');
            }
        }

        for (j=0; j<50; j++) {
            attron(COLOR_PAIR(4));
            
            switch (doors[i][j].wall) {
              case 'n':
                mvaddch(yDif[i],doors[i][j].tile+xDif[i],'+');
                break;

              case 'e':
                mvaddch(doors[i][j].tile+yDif[i],xDif[i]+rooms[i].width,'+');
                break;

              case 'w':
                mvaddch(doors[i][j].tile+yDif[i],xDif[i],'+');
                break;

              case 's':
                mvaddch(rooms[i].height+yDif[i],doors[i][j].tile+xDif[i],'+');
                break;
            }
            
            if (objects[i][j].icon!='z') {
                attron(COLOR_PAIR(objects[i][j].colour));
                mvaddch(objects[i][j].yPos+yDif[i],objects[i][j].xPos+xDif[i],objects[i][j].icon);
            }
        }
        attron(COLOR_PAIR(7));
        
        if (bronson.start==i) {
            mvaddch(bronson.yPos+yDif[i],bronson.xPos+xDif[i],'@');
        }
    }
    attron(COLOR_PAIR(7));
    mvprintw(0,0,"| ");
    attron(COLOR_PAIR(2));
    printw("Health: %d",bronson.health);
    attron(COLOR_PAIR(7));
    printw(" | ");
    attron(COLOR_PAIR(6));
    printw("Damage: %d",bronson.damage);
    attron(COLOR_PAIR(7));
    printw(" | ");
    attron(COLOR_PAIR(3));
    printw("Gold: 0");
    attron(COLOR_PAIR(7));
    printw(" | ");
    attron(COLOR_PAIR(4));
    printw("Room: %d",bronson.start+1);
    attron(COLOR_PAIR(7));
    printw(" |    ");
    move(bronson.yPos+yDif[bronson.start],bronson.xPos+xDif[bronson.start]);
    playRogue(bronson,xDif,yDif,rooms,objects);

    return;
}
