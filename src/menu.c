/*******************************menu.c*****************************************************
Date:         Monday, March 2nd, 2015         Course Name:    CIS*2500
*********************************************************************************************/

#include "main.h"
#include "menu.h"
#include "setup.h"
#include "rogue.h"

int menu(void) {
    char input = 'z';
    int yPos = 2;
    char option[3][15] = {"Play\n\0","Instructions\n\0","Highscores\n\0"};

    erase();
    move(0,0);
    attron(COLOR_PAIR(1));
    mvprintw(0,0,"Rogue-like\n\n  ");
    attron(COLOR_PAIR(8));
    printw("%s",option[0]);
    attron(COLOR_PAIR(5));
    printw("  %s",option[1]);
    attron(COLOR_PAIR(6));
    printw("  %s",option[2]);
    attron(COLOR_PAIR(7));
    mvprintw(6,0,"Use W and S keys to navigate selections.");
    mvprintw(7,0,"press ENTER when you are ready.");
    mvprintw(0,11,"by beorc-gar");

    while (input!='\n') {
        attron(COLOR_PAIR(7));
        move(yPos,2);
        input = getch();
        input = tolower(input);
        
        if (input=='q') {
            return 0;
        }
        attron(COLOR_PAIR(yPos+2));
        mvprintw(yPos,2,"%s",option[yPos-2]);

        if (input=='s' && yPos<4) {
            yPos++;
        } else if (input=='s') {
            yPos = 2;
        } else if (input=='w' && yPos>2) {
            yPos--;
        } else if (input=='w') {
            yPos = 4;
        }
        attron(COLOR_PAIR(yPos+6));
        mvprintw(yPos,2,"%s",option[yPos-2]);
    }
    
    return yPos-1;
}

void instructions(void) {
    erase();
    attron(COLOR_PAIR(4));
    mvprintw(0,0,"How to play Rogue\n");
// Objective
    attron(COLOR_PAIR(6));
    printw("\n    Objective:\n");
    attron(COLOR_PAIR(7));
    printw("\tNavigate through the rooms collecting items.\n");
    printw("\tAvoid or kill monsters. (Don't die!)\n");
    printw("\tReach the final boss room, and kill the boss.\n");
    printw("\tUse the dungeon's exit. (Guarded unless you've killed all the monsters)\n");
    printw("\tYour score is how much gold you end with. (x2 if you win)\n");
// Controls
    attron(COLOR_PAIR(6));
    printw("\n    Controls:\n");
    attron(COLOR_PAIR(7));
    printw("\tW   move north (up)   \n");
    printw("\tS   move south (down) \n");
    printw("\tA   move west  (left) \n");
    printw("\tD   move east  (right)\n");
    printw("\tQ   quit game  (return to menu)\n");
    attron(COLOR_PAIR(6));
    printw("\n    Definitions:\n\t");
// Hero
    attron(COLOR_PAIR(7));
    printw("@   hero       (you are here)\n\n\t");
// Items
    attron(COLOR_PAIR(3));
    printw("*");
    attron(COLOR_PAIR(7));
    printw("   gold       (build your score)\n\t");
    attron(COLOR_PAIR(5));
    printw("$");
    attron(COLOR_PAIR(7));
    printw("   magic      (enchant your weapon)\n\t");
    attron(COLOR_PAIR(2));
    printw("!");
    attron(COLOR_PAIR(7));
    printw("   potion     (boost your health)\n\t");
    attron(COLOR_PAIR(6));
    printw(")");
    attron(COLOR_PAIR(7));
    printw("   weapon     (fortify your weapon)\n\n\t");
// Monsters
    attron(COLOR_PAIR(1));
    printw("M");
    attron(COLOR_PAIR(7));
    printw("   monster    (wants to fight you)\n\t");
    attron(COLOR_PAIR(1));
    printw("B");
    attron(COLOR_PAIR(7));
    printw("   boss       (wants to kill you)\n\t");
    attron(COLOR_PAIR(1));
    printw("X");
    attron(COLOR_PAIR(7));
    printw("   guardian   (wants to prevent you from winning) \n\n\t");
// Architecture
    attron(COLOR_PAIR(4));
    printw("+");
    attron(COLOR_PAIR(7));
    printw("   door       (move to the nearest room)\n\t");
    attron(COLOR_PAIR(4));
    printw("%%");
    attron(COLOR_PAIR(7));
    printw("   stairs     (enter final boss room)\n\t");
    attron(COLOR_PAIR(4));
    printw("e");
    attron(COLOR_PAIR(7));
    printw("   exit       (win the game)\n\t");
    attron(COLOR_PAIR(4));
    printw("|-");
    attron(COLOR_PAIR(7));
    printw("  wall       (border)\n\t.   floor      (walk on this)\n\n");
    attron(COLOR_PAIR(4));
    printw("Press any key to return to menu.\n");
    attron(COLOR_PAIR(7));
    move(17,8);
    getch();
    erase();
    move(0,0);

    return;
}

void highScores(void) {
    FILE* filePtr = fopen("assets/HighScores.txt","r");
    char buffer[100][40];
    char names[100][20];
    char tempName[20];
    char* token;
    int scores[100] = {0};
    int i = 0;
    int j = 1;
    int num = 0;
    int tempScore = 0;

    erase();

    if (filePtr!=NULL) {
        while (fgets(buffer[i],35,filePtr)!=NULL && i<100) {
            token = strtok(buffer[i],"∞");
            
            if (token!=NULL) {
                sprintf(names[i],"%s",token);
                token = strtok(NULL,"∞");
                
                if (token!=NULL) {
                    scores[i] = atol(token);
                }
            }
            i++;
        }
        
        fclose(filePtr);
        num = i;
        
        for (i=0; i<num; i++) {
            for (j=i+1; j<num; j++) {
                while (scores[i]<scores[j]) {
                    sprintf(tempName,"%s",names[i]);
                    tempScore = scores[i];
                    scores[i] = scores[j];
                    scores[j] = tempScore;
                    sprintf(names[i],"%s",names[j]);
                    sprintf(names[j],"%s",tempName);
                }
            }
        }
        
        if (num>10) {
            num = 10;
        }
        attron(COLOR_PAIR(4));
        mvprintw(0,0,"Highscores\n");
        
        for (i=0; i<num; i++) {
            if (scores[i] > 0 && names[i]!=NULL) {
                attron(COLOR_PAIR((i%2)+5));
                
                if (i==9) {
                    mvprintw(i+2,4,"%d. %s",i+1,names[i]);
                } else {
                    mvprintw(i+2,4,"%d.  %s",i+1,names[i]);
                }
                mvprintw(i+2,25,"%d\n",scores[i]);
            }
        }
    }
    attron(COLOR_PAIR(4));
    printw("\nPress any key to return to menu.\n");
    attron(COLOR_PAIR(7));
    getch();
    
    return;
}
