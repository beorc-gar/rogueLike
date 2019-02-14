/*******************************main.c*******************************************************
Date:         Monday, March 2nd, 2015         Course Name:    CIS*2500
*********************************************************************************************/

#include "main.h"
#include "menu.h"
#include "setup.h"
#include "rogue.h"

int main(int argc,char* argv[]) {
    int choice = 4;
    if (argc!=2) {
        printf("Usage: bin/runMe <text file>\n");
        return 0;
    }

    initscr();
    start_color();
    use_default_colors();
    cbreak();
    noecho();

    init_pair(1,1,-1);   // red
    init_pair(2,2,-1);   // green
    init_pair(3,3,-1);   // yellow
    init_pair(4,4,-1);   // blue
    init_pair(5,5,-1);   // magenta
    init_pair(6,6,-1);   // cyan
    init_pair(7,-1,-1);  // default
    init_pair(8,4,0);    // highlighted blue
    init_pair(9,5,0);    // highlighted magenta
    init_pair(10,6,0);   // highlighted cyan

    attron(A_BOLD);

    while (choice!=0) {
        choice = menu();
        attron(COLOR_PAIR(7));
        erase();

        if (choice==1) {
            startGame(argv[1]);
        } else if (choice==2) {
            instructions();
        } else if (choice==3) {
            highScores();
        }
    }

    endwin();
    return 0;
}
