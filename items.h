#include<stdlib.h>

#ifndef ITEMS_HEAD
#define ITEMS_HEAD

struct Item {
	char name[33];
	char description[30];
	struct Item* next;
};

struct Item* item(char name[], char description[]);
void free_items(struct Item*);

char* get_item_name(struct Item* );

char* get_item_description(struct Item* );

struct Item* get_item_next(struct Item* );

void set_item_next(struct Item*, struct Item*);

struct Item* drop_item(struct Item* , char* );

void add_item(struct Item* , struct Item*);

void display_items(struct Item*);

int get_item_num(struct Item*);


#endif