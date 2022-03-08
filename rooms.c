#include<stdio.h>
#include<string.h>
#include "rooms.h"

//Dynamically creates an object of struct Room and returns a pointer to it
struct Room* room(char* description, struct Item* items, struct Room* north, struct Room
	* south, struct Room* east, struct Room* west) {

	struct Room* temp = (struct Room*)malloc(sizeof(struct Room));
	if (temp) {
		strcpy(temp->description, description);
		if (items) {
			temp->items = items;
		}
		else {
			temp->items = item("dummy","dummy");
		}
		temp->north = north;
		temp->south = south;
		temp->east = east;
		temp->west = west;
	}
	return temp;
}

//Deallocated the Room object pointed by its parameter
void free_room(struct Room * x) {
	free_items(x->items);
	free(x);
}

//Returns the description member of the Room object pointed by its parameter
char* get_room_description(struct Room* x) {
	return x?x->description:NULL;
}

//Returns the items member of the Room object pointed by its parameter
struct Item* get_room_items(struct Room* x) {
	return x?x->items:NULL;
}

//Sets the north member of the Room object pointed by x and also ensures the corresponding south member of the north object points to x object
void set_north(struct Room* x, struct Room* north) {
	x->north = north;
	if (north && get_south(north) != x)
	{
		if(get_south(north))
			set_north(get_south(north),NULL);
		set_south(north, x);
	}
}

//Returns the north member of the Room object pointed by its parameter
struct Room* get_north(struct Room* x) {
	return x?x->north:NULL;
}

//Sets the south member of the Room object pointed by x and also ensures the corresponding north member of the south object points to x object
void set_south(struct Room* x, struct Room* south) {
	x->south = south;
	if (south && get_north(south) != x ) {
		if (get_north(south))
			set_south(get_north(south), NULL);
		set_north(south, x);
	}
}

//Returns the south member of the Room object pointed by its parameter
struct Room* get_south(struct Room* x) {
	return x?x->south:NULL;
}

//Sets the east member of the Room object pointed by x and also ensures the corresponding west member of the east object points to x object
void set_east(struct Room* x, struct Room* east) {
	x->east = east;
	if (east && get_west(east) != x) {
		if (get_west(east))
			set_east(get_west(east), NULL);
		set_west(east, x);
	}
}

//Returns the east member of the Room object pointed by its parameter
struct Room* get_east(struct Room* x) {
	return x?x->east:NULL;
}

//Sets the west member of the Room object pointed by x and also ensures the corresponding east member of the west object points to x object
void set_west(struct Room* x, struct Room* west) {
	x->west = west;
	if (west && get_east(west) != x) {
		if (get_east(west))
			set_west(get_east(west), NULL);
		set_east(west, x);
	}
}

//Returns the west member of the Room object pointed by its parameter
struct Room* get_west(struct Room* x) {
	return x?x->west:NULL;
}

//Displays the Room object pointed by its parameter
void display_room(struct Room* entrance) {
	printf("\n\nRoom name: %s", get_room_description(entrance));
	printf("\n");
	if (get_item_next(get_room_items(entrance))) {
		printf("\n");
		for(int i =0;i<45;i++){
			printf("-");
		}
		printf("\n");
		printf("\t\tItems in the room ");
		display_items(get_room_items(entrance));
		printf("\n");
		for(int i =0;i<45;i++){
			printf("-");
		}
		printf("\n");
	}
	if (get_north(entrance)) {
		printf("\n\nNorth: %s", get_room_description(get_north(entrance)));
	}
	if (get_south(entrance)) {
		printf("\n\nSouth: %s", get_room_description(get_south(entrance)));
	}
	if (get_east(entrance)) {
		printf("\n\nEast: %s", get_room_description(get_east(entrance)));
	}
	if (get_west(entrance)) {
		printf("\n\nWest: %s", get_room_description(get_west(entrance)));
	}
}
