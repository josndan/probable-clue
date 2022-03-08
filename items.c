#include<strings.h>
#include<string.h>
#include<stdio.h>
#include "items.h"


//Dynamically creates an object of struct Character and returns a pointer to it
struct Item* item(char name[],char description[]) {
	struct Item* temp = (struct Item*)malloc(sizeof(struct Item));
	if (temp) {
		strcpy(temp->name, name);
		strcpy(temp->description, description);
		temp->next = NULL;
	}
	return temp;
}

//Returns the name member of the Item object pointed by its parameter
char* get_item_name(struct Item* x) {
	return x->name;
}

//Returns the description member of the Item object pointed by its parameter
char* get_item_description(struct Item* x) {
	return x?x->description:NULL;
}

//Returns the next member of the Item object pointed by its parameter
struct Item* get_item_next(struct Item* x) {
	return x?x->next:NULL;
}

//Sets the next member of the Item object pointed by its parameter
void set_item_next(struct Item* x, struct Item* next) {
	x->next=next;
}

//Deallocated the Item object pointed by its parameter
void free_items(struct Item* x) {
	if (get_item_next(x))
		free_items(get_item_next(x));
	free(x);
}

//Removes the items pointed by name from the linked list pointed by head 
struct Item* drop_item(struct Item* head, char* name) {
	struct Item* prev = head, * temp;
	if (head) //make sures dummy(first element) can never be removed
		head = get_item_next(head);
	temp = head;
	while (temp != NULL) {
		if (strcasecmp(get_item_name(temp), name) == 0) {
			prev->next = get_item_next(temp);
			set_item_next(temp,NULL);
			return temp;
		}
		prev = temp;
		temp = get_item_next(temp);
	}
	return NULL;
}


//Adds the items pointed by item from the linked list pointed by head 
void add_item(struct Item* head, struct Item* item) {
	while (head)
	{
		if(get_item_next(head))
			head = get_item_next(head);
		else {
			set_item_next(head,item);
			return;
		}
	}
}

//Displays the Item object pointed by its parameter
void display_items(struct Item* head) {
	if (strcmp(get_item_name(head), "dummy") != 0) 
		printf("\nName: %s ; Description: %s", get_item_name(head), get_item_description(head));
	if (get_item_next(head)) {
		display_items(get_item_next(head));
	}
}

//Returns the number of items in the linked list pointed by head
int get_item_num(struct Item* head) {
	int n = 1;
	while (head)
	{
		if (get_item_next(head)) {
			head = get_item_next(head);
			n += 1;
		} else
			return n;
	}
	return 0;
}
