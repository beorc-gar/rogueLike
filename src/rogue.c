/*******************************rogue.c*****************************************************
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

void playRogue(hero bronson,int xDif[],int yDif[],room* rooms,object** monsters) {
    char input = 'z';
    char nextC = 'z';
    int magicLeft = 21;
    int potionLeft = 21;
    int moveX = 0;
    int moveY = 0;
    int i = 0;
    int gold = 0;
    int potions = 0;
    int weapons = 0;
    int magic = 0;
    object boss;
    object bonusBoss;
    
    bonusBoss.icon = '.';
    bonusBoss.xPos = 25;
    bonusBoss.yPos = 35;
    bonusBoss.health = 0;
    bonusBoss.damage = 0;
    bonusBoss.speed = 0;
    bonusBoss.start = 0;
    bonusBoss.colour = 1;
    boss.colour = 1;
    boss.icon = 'b';

    srand(time(NULL));

    while (input!='q') {
        input = getch();
        input = tolower(input);
        
        switch (input) {
          case 'w':
            moveX = 0;
            moveY = -1;
            break;

          case 's':
            moveX = 0;
            moveY = 1;
            break;

          case 'a':
            moveX = -1;
            moveY = 0;
            break;

          case 'd':
            moveX = 1;
            moveY = 0;
            break;

          default:
            moveX = 0;
            moveY = 0;
            break;
        }
        
        if (magicLeft>0 && magicLeft<21) {
            magicLeft--;
        } else if (magicLeft!=21) {
            magicLeft = 21;
            bronson.damage -= 5;
        }
        
        if (potionLeft>0 && potionLeft<21) {
            potionLeft--;
            bronson.health += 2;
        } else if (potionLeft!=21) {
            potionLeft = 21;
        }
        nextC = mvinch(bronson.yPos+yDif[bronson.start]+moveY,bronson.xPos+xDif[bronson.start]+moveX);
        
        if (nextC=='+') {
            newRoom(&bronson,moveX,moveY,xDif,yDif);
        } else if (nextC=='e') {
            boss.icon = '.';
            input = 'q';
            endGame(bronson,gold,magic,weapons,potions);
        } else if (nextC=='%') {
            makeBossRoom(&bronson,&boss,&bonusBoss,monsters);
        } else if (nextC=='B') {
            hitMob(&bronson,&boss,yDif,xDif);
        } else if (nextC=='X') {
            hitMob(&bronson,&bonusBoss,yDif,xDif);
        } else if (nextC=='M') {
            for (i=0; i<9; i++) {
                if (monsters[bronson.start][i].icon=='M' && ((abs(bronson.xPos-monsters[bronson.start][i].xPos)==0 && (abs(bronson.yPos-monsters[bronson.start][i].yPos)==1)) || (abs(bronson.xPos-monsters[bronson.start][i].xPos)==1 && abs(bronson.yPos-monsters[bronson.start][i].yPos)==0))) {
                    hitMob(&bronson,&monsters[bronson.start][i],yDif,xDif);
                }
            }
        } else if (nextC!='-' && nextC!='|') {
            mvaddch(bronson.yPos+yDif[bronson.start],bronson.xPos+xDif[bronson.start],'.');
            
            switch (nextC) {
              case '*':
                gold += (rand() % 10) + 1;
                break;

              case '$':
                magicLeft = 20;
                bronson.damage += 5;
                magic++;
                break;

              case '!':
                potionLeft = 20;
                potions++;
                break;

              case ')':
                bronson.damage += 10;
                weapons++;
                break;
            }
            attron(COLOR_PAIR(7));
            mvaddch(bronson.yPos+yDif[bronson.start]+moveY,bronson.xPos+xDif[bronson.start]+moveX,'@');
            bronson.yPos += moveY;
            bronson.xPos += moveX;
        }
        
        if (bronson.health<1) {
            endGame(bronson,gold,magic,weapons,potions);
            input = 'q';
        }
        
        for (i=0; i<9; i++) {
            if (monsters[bronson.start][i].icon=='M') {
                mobMove(bronson,&monsters[bronson.start][i],yDif,xDif);
            }
        }
        
        if (boss.icon=='B' && boss.health>0) {
            mobMove(bronson,&boss,yDif,xDif);
        }
        showStats(bronson,gold,boss,bonusBoss);
        attron(COLOR_PAIR(7));
        mvaddch(bronson.yPos+yDif[bronson.start],bronson.xPos+xDif[bronson.start],'@');
        move(bronson.yPos+yDif[bronson.start],bronson.xPos+xDif[bronson.start]);
    }
    return;
}

void addScore(char name[],int gold,int mult) {
    FILE* filePtr;
    int i = 0;

    for (i=0; i<20; i++) {
        if (name[i]=='\n' || i==19) {
            name[i]='\0';
            i = 20;
        }
    }

    filePtr = fopen("assets/HighScores.txt","a");
    if (filePtr!=NULL) {
        fprintf(filePtr,"%s∞%d\n",name,gold*mult);
        fclose(filePtr);
    }
    return;
}

void newRoom(hero* bronson,int moveX,int moveY,int xDif[],int yDif[]) {
    char check = 'z';
    mvaddch(bronson->yPos+yDif[bronson->start],bronson->xPos+xDif[bronson->start],'.');
    bronson->xPos = 1;
    bronson->yPos = 1;
    
    if (moveX==-1) {
        if (bronson->start==0) {
            bronson->start = 5;
        } else {
            bronson->start -= 1;
        }
    } else if (moveX==1) {
        if (bronson->start==5) {
            bronson->start = 0;
        } else {
            bronson->start+=1;
        }
    }
    
    if (moveY==-1) {
        if (bronson->start>2) {
            bronson->start -= 3;
        } else {
            bronson->start += 3;
        }
    } else if (moveY==1) {
        if (bronson->start<=2) {
            bronson->start += 3;
        } else {
            bronson->start -= 3;
        }
    }
    check = mvinch(bronson->yPos+yDif[bronson->start],bronson->xPos+xDif[bronson->start]);
    
    while (check!='.') {
        bronson->xPos++;
        check = mvinch(bronson->yPos+yDif[bronson->start],bronson->xPos+xDif[bronson->start]);
        if (check=='@') {
            check = '.';
        }
    }
    attron(COLOR_PAIR(7));
    addch('@');

    return;
}

void endGame(hero bronson,int gold,int magic,int weapons,int potions) {
    int mult = 1;
    char player[20];
    
    erase();
    
    if (bronson.health>0) {
        attron(COLOR_PAIR(2));
        mvprintw(0,0,"Congratulations! You Win!\n\n");
        mult = 2;
    } else {
        attron(COLOR_PAIR(1));
        mvprintw(0,0,"Too bad! You Lose!\n\n");
        bronson.health = 0;
        mult = 1;
    }
    attron(COLOR_PAIR(2));
    printw("Health:  %d\n",bronson.health);
    attron(COLOR_PAIR(3));
    printw("Gold:    %d\n",gold);
    attron(COLOR_PAIR(4));
    printw("Potions: %d\n",potions);
    attron(COLOR_PAIR(5));
    printw("Magic:   %d\n",magic);
    attron(COLOR_PAIR(6));
    printw("Weapons: %d\n",weapons);
    attron(COLOR_PAIR(7));
    printw("\nEnter your name: ");
    
    echo();
    getstr(player);
    noecho();
    addScore(player,gold,mult);

    return;
}

void makeBossRoom(hero* bronson,object* boss,object* bonusBoss,object** monsters) {
    int i = 0;
    int j = 0;

    erase();
    
    for (i=0; i<6; i++) {
        for (j=0; j<50; j++) {
            if (monsters[i][j].icon=='M') {
                bonusBoss->damage += monsters[i][j].damage + 2;
                bonusBoss->health += monsters[i][j].health + 5;
                bonusBoss->icon = 'X';
            }
        }
    }
    attron(COLOR_PAIR(4));
    
    for (i=0; i<50; i++) {
        mvaddch(1,i,'-');
        mvaddch(37,i,'-');
    }
    
    for (i=1; i<37; i++) {
        mvaddch(i,0,'|');
        mvaddch(i,49,'|');
    }
    attron(COLOR_PAIR(7));

    for (i=2; i<37; i++) {
        for (j=1; j<49; j++) {
            mvaddch(i,j,'.');
        }
    }
    attron(COLOR_PAIR(5));
    mvaddch(36,48,'$');
    mvaddch(2,1,'$');
    attron(COLOR_PAIR(2));
    mvaddch(2,48,'!');
    mvaddch(36,1,'!');
    attron(COLOR_PAIR(6));
    mvaddch(17,48,')');
    mvaddch(17,1,')');
    attron(COLOR_PAIR(1));
    
    if (bonusBoss->icon=='.')
    {
        attron(COLOR_PAIR(7));
    }
    mvaddch(36,25,bonusBoss->icon);
    mvaddch(18,25,'B');
    attron(COLOR_PAIR(7));
    mvaddch(2,25,'@');

    boss->xPos = 25;
    boss->yPos = 17;
    boss->health = 350;
    boss->speed = 1;
    boss->damage = 35;
    boss->icon = 'B';
    boss->start = 0;
    bronson->health += 20;
    bronson->xPos = 25;
    bronson->yPos = 1;
    bronson->start = 0;

    return;
}

void hitMob(hero* bronson,object* mob,int yDif[],int xDif[]) {
    char loot = '*';
    int roll = 2;
    int i = 0;

    bronson->health -= mob->damage;
    mob->health -= bronson->damage;

    if (mob->health<1) {
        mvaddch(mob->yPos+yDif[bronson->start],mob->xPos+xDif[bronson->start],'.');

        if (mob->icon=='B') {
            attron(COLOR_PAIR(4));
            mvaddch(37,25,'e');
            attron(COLOR_PAIR(3));
            
            for (i=0; i<(rand()%30)+10; i++) {
                if (mvinch((rand()%36)+2,(rand()%48)+1)!='.') {
                    addch('*');
                }
            }
        } else if (mob->icon=='M') {
            mob->icon = '.';
            roll = rand()%4;
            
            switch (roll) {
              case 0:
                loot = '!';
                attron(COLOR_PAIR(2));
                break;

              case 1:
                loot = ')';
                attron(COLOR_PAIR(6));
                break;

              case 2:
                loot = '*';
                attron(COLOR_PAIR(3));
                break;

              case 3:
                loot = '$';
                attron(COLOR_PAIR(5));
                break;

              default:
                loot = '*';
                attron(COLOR_PAIR(3));
                break;
            }
            mvaddch(mob->yPos+yDif[bronson->start],mob->xPos+xDif[bronson->start],loot);
        }
        mob->health = 0;
        mob->damage = 0;
        mob->start = -1;
        mob->speed = 0;
        mob->xPos = -1;
        mob->yPos = -1;
    }

    return;
}

void mobMove(hero bronson,object* mob,int yDif[],int xDif[]) {
    int aggroX = 0;
    int aggroY = 0;
    char check = 'z';

    move(mob->yPos+yDif[bronson.start],mob->xPos+xDif[bronson.start]);
    
    if (mob->xPos-bronson.xPos>0) {
        aggroX = -1;
    } else if (mob->xPos-bronson.xPos<0) {
        aggroX = 1;
    } else {
        aggroX = 0;
    }
    
    if (mob->yPos-bronson.yPos>0) {
        aggroY = -1;
    } else if (mob->yPos-bronson.yPos<0) {
        aggroY = 1;
    } else {
        aggroY = 0;
    }
    attron(COLOR_PAIR(7));
    addch('.');
    check = mvinch(mob->yPos+aggroY+yDif[bronson.start],mob->xPos+aggroX+xDif[bronson.start]);
    
    if (check=='.') {
        mob->yPos += aggroY;
        mob->xPos += aggroX;
    }
    attron(COLOR_PAIR(1));
    mvaddch(mob->yPos+yDif[bronson.start],mob->xPos+xDif[bronson.start],mob->icon);

    return;
}

void showStats(hero bronson,int gold,object boss,object bonusBoss) {
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
    printw("Gold: %d",gold);
    attron(COLOR_PAIR(7));
    printw(" | ");
    attron(COLOR_PAIR(4));
    printw("Room: %d",bronson.start+1);
    attron(COLOR_PAIR(7));
    printw(" |     ");
    
    if (boss.icon=='B') {
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
        printw("Gold: %d",gold);
        attron(COLOR_PAIR(7));
        printw(" | ");
        attron(COLOR_PAIR(4));
        printw("Room: Boss");
        attron(COLOR_PAIR(7));
        printw(" |     ");
        mvprintw(38,0,"| ");
        attron(COLOR_PAIR(1));
        printw("Boss Health: %d",boss.health);
        attron(COLOR_PAIR(7));
        printw(" | ");
        
        if (bonusBoss.icon=='X') {
            attron(COLOR_PAIR(1));
            printw("Guardian Health: %d",bonusBoss.health);
            attron(COLOR_PAIR(7));
            printw(" |     ");
        } else {
            printw("    ");
        }
    }

    return;
}
