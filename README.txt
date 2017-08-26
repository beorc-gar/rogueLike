*******************************************************************************
                             ~Authorship~
*******************************************************************************

Bronson Graansma 0872249

*******************************************************************************
                            ~Compilation~
*******************************************************************************

Be sure to be situated in the A3 directory, then type "make".

*******************************************************************************
                             ~Execution~
*******************************************************************************

Be sure to be situated in the A3 directory, then type "bin/runMe " followed by
the name of the file you are using to determine how the rooms are set up.
( usage: bin/runMe <fileName> )

If you happened to enter a file name that can't be found, a default level is
generated instead. And if the file for this default level can't be found,
the program stops and exits safely.

Once exectuted, navigate the menu using W (up) and S (down) to select what to
do next. Press ENTER to make this selection, or just press Q to quit.
Possible selections are:
    Play         - Generates the dungeon from input file to interact with.
    Instructions - Tells you how to play.
    Highscores   - Displays top (10) players and their scores.
                 - If there are less than 10 players, all players are top.
For Highscores and Instructions, pressing any key will return to main menu.
While playing the game, these are the controls:
    W - move north (up)
    A - move west (left)
    S - move south (down)
    D - move east (right)
    Q - return to main menu
    Any other key will be ignored, but will still count as a turn. This means
    monsters can still move towards you, and your potions or magic will still
    deplete.

Various characters in the game are as follows:
  Mobs
    @   The hero, this is you, you control this using the WASD keys.
    M   A monster, these can be engaged in combat with you, and will chase you.
          Walk into this to engage combat. Drops a random item when killed.
    B   A boss, this can be engaged in combat with you, and will chase you.
          Walk into this to engage combat. Drops 10-30 piles of gold randomly
          throughout the room when killed.
    X   A guardian, this can be engaged in combat with you, and will block the
          dungeon's exit. Walk into this to engage combat. This only spawns if
          all the monsters in the dungeon haven't been killed. It's health
          and damage is proportionally greater than the sum of all the monsters
          health and damage that are still alive when you enter the boss room.

  Items
    !   A potion, heals you for 2 health for each of your next 20 turns.
    $   Increases your weapon damage by 5 for your next 20 turns.
    *   A pile of gold, you collect anywhere from 1-10 peices of gold.
    )   A weapon, increases your weapon damage by 10 permanently.

  Architecture
    |-  The walls, prevents you from quantum tunneling out of the dungeon.
    +   A door, allows you to go to the closest room. The closest room is:
          East facing doors in eastern rooms: the western most room.  
          East facing doors: the room to the east.
          West facing doors in western rooms: the eastern most room.
          West facing doors: the room to the west.
          North facing doors in northern rooms: the room to the south.
          North facing doors: the room to the north.
          South facing doors in southern rooms: the room to the north.
          South facing doors: the room to the south.
    %   A staircase, brings you to the boss room.
    e   The dungeon's exit, wins and ends the game.

*******************************************************************************
                             ~Known Limitations~
*******************************************************************************
1. After you go into instructions, back out, start a game, quit, and start
   another game, there are a few potions just outside the walls of a few rooms.

2. Can't use negative numbers if they are in the input file.

3. If the coordinates for an item is larger than the dimensions of the room, 
   the item will be placed outside the room (where it would be if the room
   where large enough to hold that coordinate).

*******************************************************************************
                               ~Enhancements~
*******************************************************************************
- Combat
- Items do things
- Monsters chase you
- Boss room generation for staircase

-------------------------------------------------------------------------------
Tested on: | SoCS Raspbian | Ubuntu 14.10 LTS |
