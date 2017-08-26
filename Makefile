all:
	gcc -Wall -pedantic -std=c99 -Iinclude src/main.c src/menu.c src/setup.c src/rogue.c -o bin/runMe -lncurses
