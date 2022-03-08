Implementation Details of commandline based Clue game using C.

Demo: https://youtu.be/EBThHjEBmEs

The game has a 3x3 array which contains pointer to nine different Room objects. (Line 54 in adventure.c)

The game randomly initializes the location of each room in the 3x3 array. (Line 44 to 69 in adventure.c)

The game has 5 characters excluding the player and their locations are randomly
initialized in one of the 9 rooms. (Line 82 adventure.c)

The game has 6 items and location of each item is randomly chosen. A room has
at most 1 item. (Line 77 in adventure.c)

The game randomly chooses a room, an item and a character as the answer.(Line 85 in adventure.c)

Each room has a linked list of items. (Line 8 in rooms.h)

The game has the following commands:

             COMMAND     DESCRIPTION

                help     Displays all the commands. (implemented in case 1 of the switch case)

                list     Displays the list of items, rooms and characters. (implemented in case 2 of the switch case)

                look     Helps you see the room by displays rooms in each direction, the
                         characters in the room and items in the room. (implemented in case 3 of the switch case)

        go DIRECTION     Helps you move between rooms where DIRECTION is one of the
                         four directions: north, south, east, west. (implemented in case 4,5,6,7 of the switch case)

           take ITEM     Pick the item where ITEM is the name of the item. (implemented in case 8 of the switch case)

           drop ITEM     Drops the item where ITEM is the name of item. (implemented in case 9 of the switch case)

           inventory     Displays all the items in your inventory. (implemented in case 10 of the switch case)

      clue CHARACTER     Make a guess where CHARACTER is the name of a character. (implemented in case 11 of the switch case)

Each character in the game has an inventory (a linked list of items) but the
inventory of non players are always empty. (Line 9 characters.h)

When the clue command is given by the player, the game moves the stated character
to the player's room and displays the game status based on the following rules:
      "Room match" - if the player is in the room of the answer.  (Line 177 in adventure.c)
      "Character Match" - if the player is in the same room as the character of answer. (Line 188 in adventure.c)
      "Item Match" - if the item of answer is either in the inventory of the player or is in the
                     current room. (Line 198 to 213 adventure.c)

If the player hits the all 3 matches in 1 clue command then the player wins. (Line 223 in adventure.c)
If the player didn't hit all 3 matches after the 10th clue command, then the player loses. (Line 228 in adventure.c)
