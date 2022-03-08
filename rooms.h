#include "items.h"

#ifndef ROOMS_HEAD
#define ROOMS_HEAD

struct Room {
	char description[30];
	struct Item* items;
	struct Room* north, * south, * east, * west;
};

struct Room* room(char*, struct Item*, struct Room*, struct Room*, struct Room*, struct Room*);
void free_room(struct Room*);

char* get_room_description(struct Room*);
struct Item* get_room_items(struct Room*);

void set_north(struct Room* , struct Room* );
struct Room* get_north(struct Room* );

void set_south(struct Room* , struct Room* );
struct Room* get_south(struct Room* );

void set_east(struct Room* , struct Room* );
struct Room* get_east(struct Room* x);

void set_west(struct Room* , struct Room* );
struct Room* get_west(struct Room* );


void display_room(struct Room*);


#endif