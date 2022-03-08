#include<stdio.h>
#include<string.h>
#include "characters.h"

//Dynamically creates an object of struct Character and returns a pointer to it
struct Character* character(char name[], struct Item* bag, struct Room* curr_room) {
	struct Character* temp = (struct Character*)malloc(sizeof(struct Character));
	if (temp) {
		strcpy(temp->name,name);
		if (bag) {
			temp->bag = bag;
		}
		else {
			temp->bag = item("dummy", "dummy");
		}
		temp->curr_room = curr_room;
	}
	return temp;
}

//Deallocated the character object pointed by its parameter
void free_character(struct Character *x) {
	free_items(x->bag);
	free(x);
}

//Returns the bag member of the Character object pointed by its parameter
struct Item* get_character_items(struct Character* x) {
	return x?x->bag:NULL;
}

//Returns the name member of the Character object pointed by its parameter
char* get_character_name(struct Character* x) {
	return x?x->name:NULL;
}

//Returns the curr_room member of the Character object pointed by its parameter
struct Room* get_character_curr_room(struct Character* x) {
	return x?x->curr_room:NULL;
}

//Modifies the curr_room member of the Character object pointed by its parameter
void move_character(struct Character* x, struct Room* curr_room) {
	x->curr_room = curr_room;
}

//Displays the Character object pointed by its parameter
void display_character(struct Character* x,int loc) {
	printf("\n%s", get_character_name(x));
	if (get_item_next(get_character_items(x))) {
		printf("\nInventory");
		display_items(get_character_items(x));
	}
	if (loc)
		printf("\nLocation :%s",get_room_description(get_character_curr_room(x)));
	printf("\n\n");
}
