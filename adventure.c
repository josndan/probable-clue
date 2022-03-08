#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<strings.h>
#include <string.h>
#include "characters.h"
#include "items.h"
#include "rooms.h"

#define NON_PLAYER_NUM 5
#define ROOM_NUM 9
#define ITEM_NUM 6

int menu(char*);
void help();
void list(struct Room*[3][3],struct Character*, struct Character*[], struct Item* []);
void look(struct Character*, struct Character*[]);
void extract_name(char[], char[]);
struct Character* get_character_by_name(struct Character* non_player[], char name[]);
void display_hyphen(int );
void display_star(int);
int get_random_num(int);
int get_room_index_by_name(char[][30], char[]);

int main() {
	srand(time(0));
	char room_names[ROOM_NUM][30] = { "Living Room", "Dining Room", "Kitchen", "Wine Cellar", "Restroom", "Garage", "Attic", "Utility Room", "Nursery" };
	char item_names[ITEM_NUM][30] = {"Knife", "Rope", "Pillow", "Vase", "Cane", "Sword"};
	char item_descrip[ITEM_NUM][30] = {"Kitchen Knife", "Skipping Rope", "Sleeping Pillow", "Flower vase", "Assistive Cane", "Fighting Sword"};
	char character_names[NON_PLAYER_NUM][30] = {"Adam", "Eve", "Catherine", "Tom", "John"};
	char room_match[30], character_match[30], item_match[30];
	struct Room* entrance=NULL, *rooms[ROOM_NUM],* game_board[3][3];
	struct Item* temp_item=NULL, *items[ITEM_NUM];
	struct Character* player, * non_player[NON_PLAYER_NUM],*temp_character;
	char input[30] = "",name[20]="";
	int attempt_num = 0,room_found=0,item_found=0,character_found=0,choice =-1,rand_num=-1;
	
	//Intializing the game_board to NULL
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			game_board[i][j] = NULL;
		}
	}

	//Placing random rooms in the 3x3 game_board and intializing the rooms array
	for (int i = 0; i < ROOM_NUM; i++) {
		int j, k;
		j = get_random_num(3) - 1;
		k = get_random_num(3) - 1;
		while (game_board[j][k]) {
			j = get_random_num(3) - 1;
			k = get_random_num(3) - 1;
		}
		rooms[i] = room(room_names[i],NULL, NULL, NULL, NULL, NULL);
		game_board[j][k] = rooms[i];
		
	}

	//Linking the adjacent rooms in the game_board
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) {
			if (j + 1 < 3) {
				set_east(game_board[i][j],game_board[i][j+1]);
			}
			if (i + 1 < 3) {
				set_south(game_board[i][j], game_board[i + 1][j]);
			}
		}
	}

	//Creating and placing every item in a random room
	for (int i = 0; i < ITEM_NUM; i++) {
		items[i] = item(item_names[i],item_descrip[i]);
		rand_num = get_random_num(ROOM_NUM) - 1;
		while (get_item_num(get_room_items(rooms[rand_num])) > 1)
			rand_num = get_random_num(ROOM_NUM) - 1;
		add_item(get_room_items(rooms[rand_num]), items[i]);
	}

	//Creating and placing every non-player character in a random room
	for (int i = 0; i < NON_PLAYER_NUM; i++) {
		non_player[i] = character(character_names[i],NULL, rooms[get_random_num(ROOM_NUM) - 1]);
	}

	//Randomly Picking a room, an item and a character as the answer
	strcpy(room_match, room_names[get_random_num(ROOM_NUM)-1]);
	strcpy(character_match, character_names[get_random_num(NON_PLAYER_NUM) - 1]);
	strcpy(item_match, item_names[get_random_num(ROOM_NUM) - 1]);

	//randomly choosing an en entry point to the board
	entrance = rooms[get_random_num(ROOM_NUM)-1];

	//Making user's player
	printf("Enter your name: ");
	fgets(input, sizeof(input),stdin);
	input[strlen(input) - 1] = '\0';
	player = character(input, NULL, entrance);

	//Displays game start header
	display_star(90);
	printf("\t\t\t\t\tGame Begins\n");
	display_star(90);
	help(); 

	do {
		room_found = item_found = character_found = 0;
		display_hyphen(90);
		printf("Enter Command: "); // gets user command
		fgets(input, sizeof(input), stdin);
		input[strlen(input) - 1] = '\0';
		choice = menu(input); //Interprets the input and gives a choice number
		switch (choice)
		{
		case 1: 
			help();
			break;
		case 2: 
			list(game_board,player,non_player,items);
			break;
		case 3: 
			look(player,non_player);
			break;
		case 4: 
			if (get_north(get_character_curr_room(player))) //Checking the north of current room is not null
				move_character(player, get_north(get_character_curr_room(player))); // Move the player to the north of the current room
			else
				printf("\nNo room in north");
			break;
		case 5: 
			if (get_south(get_character_curr_room(player)))//Checking the south of current room is not null
				move_character(player, get_south(get_character_curr_room(player)));// Move the player to the south of the current room
			else
				printf("\nNo room in South");
			break;
		case 6: 
			if (get_east(get_character_curr_room(player)))//Checking the east of current room is not null
				move_character(player, get_east(get_character_curr_room(player)));// Move the player to the east of the current room
			else
				printf("\nNo room in East");
			break;
		case 7: 
			if (get_west(get_character_curr_room(player)))//Checking the west of current room is not null
				move_character(player, get_west(get_character_curr_room(player)));// Move the player to the west of the current room
			else
				printf("\nNo room in west");
			break;
		case 8: 
			extract_name(input, name);
			temp_item = drop_item(get_room_items(get_character_curr_room(player)), name); //Dropping the given item from the room's linked list
			if (temp_item) //Checking if the item was there in the room
				add_item(get_character_items(player), temp_item); // Adding that item to the player's inventory
			else
				printf("\nEnter valid Item name");
			break;
		case 9: 
			extract_name(input, name);
			temp_item = drop_item(get_character_items(player), name);//Dropping the given item from the player's inventory
			if (temp_item)//Checking if the item was there in the player's inventory
				add_item(get_room_items(get_character_curr_room(player)), temp_item); // Adding that item to the Room
			else
				printf("\nEnter valid Item name");
			break;
		case 10: 
			if (get_item_next(get_character_items(player))) // Checking is an item other than the dummy is there in the player's inventory
				display_items(get_character_items(player)); // Displays the player's inventory
			else
				printf("\nInventory is empty");
			break;
		case 11:
			extract_name(input, name);
			temp_character = get_character_by_name(non_player, name);
			if (temp_character) //Checking if there is a character with the given name
			{
				move_character(temp_character, get_character_curr_room(player)); //Moves the character specified by the user to the user's current room
				if (get_character_curr_room(player) == rooms[get_room_index_by_name(room_names,room_match)] ) //Checking if the current room is the answer
				{
					printf("\nRoom Match");
					room_found = 1;
				}

				temp_character = get_character_by_name(non_player, character_match);//Getting the answer character
				
				//Checking if the answer character is in the current room
				for (int i = 0; i < NON_PLAYER_NUM; i++) {
					if (get_character_curr_room(non_player[i]) == get_character_curr_room(player)) {
						if (non_player[i] == temp_character )
						{
							printf("\nCharacter Match");
							character_found = 1;
							break;
						}
					}
				}

	
				temp_item = drop_item(get_character_items(player),item_match );// Removing the answer item from the player's inventory

				if (temp_item)//Checking if the removed is not null (if null it implies it wasn't in the inventory)
				{
					add_item(get_character_items(player), temp_item);//Adding the dropped item back into the player's inventory
					printf("\nItem Match");
					item_found = 1;
				}
				else {
					temp_item = drop_item(get_room_items(get_character_curr_room(player)), item_match );//Removing the answer item from the room
					
					if (temp_item) //Checking if the removed is not null (if null it implies it wasn't in the room)
					{
						add_item(get_room_items(get_character_curr_room(player)), temp_item);//Adding the dropped item back into the room
						printf("\nItem Match");
						item_found = 1;
					}
				}
				if(!room_found && !item_found && !character_found)
					printf("\nNone of the answers match\n");
				attempt_num++;
			}
			else
				printf("\nEnter a valid character");
			break;
		case 12:
			printf("\nquiting\n");
			exit(0);
			break;
		default:
			printf("\nEnter a valid Command");
			break;
		}
	} while (attempt_num <10 && !(room_found && character_found && item_found));

	if (room_found && character_found && item_found)
		printf("\nYou won");
	else
		printf("\nYou lost");

	//Deallocating all the memory given for the rooms
	for (int i = 0; i < ROOM_NUM; i++) {
		free_room(rooms[i]);
	}

	//Deallocating all the memory given for the non-players
	for (int i = 0; i < NON_PLAYER_NUM; i++) {
		free_character(non_player[i]);
	}

	//Deallocating all the memory given for the players
	free_character(player);

	//All the items are either in the room's linked list or in the character's linked list. They are deallocated when the room/character are deallocated

	return 0;
}


//Interprest the input and returns a choice number
int menu(char *input) {
	int choice = -1;
	if (strcasecmp(input, "help") == 0) {
		choice = 1;
	}else if (strcasecmp(input, "list") == 0) {
		choice = 2;
	}else if (strcasecmp(input, "look") == 0) {
		choice = 3;
	}else if (strcasecmp(input, "go north") == 0) {
		choice = 4;
	}
	else if (strcasecmp(input, "go south") == 0) {
		choice = 5;
	}
	else if (strcasecmp(input, "go east") == 0) {
		choice = 6;
	}
	else if (strcasecmp(input, "go west") == 0) {
		choice = 7;
	}
	else if (strncasecmp(input, "take ",5) == 0) {
		choice = 8;
	}
	else if (strncasecmp(input, "drop ",5) == 0) {
		choice = 9;
	}
	else if (strcasecmp(input, "inventory") == 0) {
		choice = 10;
	}
	else if (strncasecmp(input, "clue ",5) == 0) {
		choice = 11;
	}
	else if(strcasecmp(input,"exit")==0 ){
		choice = 12;
	}
	return choice;
}

//Returns a random number from the range of 1 to end
int get_random_num(int end) {
	return (rand() % end) + 1;
}

//Returns the index of the given room name in the rooms/room_names(their index corresponds to the same room) array
int get_room_index_by_name(char x[][30],char y[])
{
	for (int i = 0; i < ROOM_NUM; i++) {
		if (strcasecmp(x[i], y) == 0)
			return i;
	}
	return -1;
}

//Puts the substring of input(from index 5 to end) in name
void extract_name(char input[],char name[]) {
	for (int i = 5;; i++) {
		if (input[i] == '\0') {
			name[i - 5] = '\0';
			break;
		}
		name[i - 5] = input[i];
	}
}

//Display a line of stars with n stars in one line
void display_star(int n) {
	printf("\n");
	for (int i = 0; i <n; i++) {
		printf("*");
	}
	printf("\n");
}

//Display a line of hyphen with n hyphen in one line
void display_hyphen(int n) {
	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("-");
	}
	printf("\n");
}

//Displays the available commands
void help() {
	printf("\n");
	display_hyphen(90);
	printf("\t\t\t\t\tList of Commands\n");
	display_hyphen(90);
	printf("\n");

	printf("%20s", "COMMAND");
	printf("\t DESCRIPTION");
	printf("\n\n");

	printf("%20s", "help");
	printf("\t Displays all the commands");
	printf("\n\n");

	printf("%20s", "list");
	printf("\t Displays the list of items,rooms and characters");
	printf("\n\n");

	printf("%20s", "look");
	printf("\t Helps you see the room by displays rooms in each direction, the");
	printf("\n%20s \t%s","","characters in the room and items in the room");
	printf("\n\n");

	printf("%20s", "go DIRECTION");
	printf("\t Helps you move between rooms where DIRECTION is one of the four");
	printf("\n%20s \t%s",""," directions: north, south, east, west");
	printf("\n\n");

	printf("%20s", "take ITEM");
	printf("\t Pick the item where ITEM is the name of the item");
	printf("\n\n");

	printf("%20s", "drop ITEM");
	printf("\t Drops the item where ITEM is the name of item");
	printf("\n\n");

	printf("%20s", "inventory");
	printf("\t Displays all the items in your inventory");
	printf("\n\n");

	printf("%20s", "clue CHARACTER");
	printf("\t Make a guess where CHARACTER is the name if a character");
	printf("\n\n");
	
	printf("%20s","exit");
	printf("\t Exit the game");
	printf("\n\n");
}

//Displays all the characters, rooms and items in the game.
void list(struct Room* game_board[3][3], struct Character* player, struct Character* non_player[],struct Item* items[]) {
	printf("\n\t\t\t\t\tROOMS\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			display_room(game_board[i][j]);
			if(i!=2 || j!=2)
				display_star(67);
		}
	}
	display_hyphen(90);
	printf("\t\t\t\t\tCHARACTERS\n");
	display_character(player,1);
	for (int i = 0; i < NON_PLAYER_NUM; i++) {
		display_character(non_player[i],1);
	}
	display_hyphen(90);
	printf("\t\t\t\t\tITEMS\n");
	for (int i = 0; i < ITEM_NUM;i++) {
		display_items(items[i]);
	}
}

//Displays a list of rooms in each direction, the characters in the room and items in the room
void look(struct Character* player, struct Character* non_player[]) {
	int disp =0;
	display_room(get_character_curr_room(player));
	printf("\n");
	for (int i = 0; i < NON_PLAYER_NUM; i++) {
		if (get_character_curr_room(non_player[i]) ==
get_character_curr_room(player)){
			if(!disp){
				printf("\nCharacters in room\n");
				disp =1;
				}
			display_character(non_player[i],0);
			}
	}
}

//Returns the character, whose name is the name array, from the non_player array
struct Character* get_character_by_name(struct Character* non_player[], char name[]) {
	for (int i = 0; i < NON_PLAYER_NUM; i++) {
		if (strcasecmp(get_character_name(non_player[i]), name) == 0)
			return non_player[i];
	}
	return NULL;
}
