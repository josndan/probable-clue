#include "items.h"
#include "rooms.h"

#ifndef CHARACTERS_HEAD
#define CHARACTERS_HEAD

struct Character {
	char name[30];
	struct Item* bag;
	struct Room* curr_room;
};

struct Character* character(char[], struct Item* , struct Room*);
void free_character(struct Character*);

char* get_character_name(struct Character* );

struct Room* get_character_curr_room(struct Character* );
void move_character(struct Character* , struct Room* );

struct Item* get_character_items(struct Character* );
void display_character(struct Character*,int);

#endif // !CHARACTERS_HEAD
