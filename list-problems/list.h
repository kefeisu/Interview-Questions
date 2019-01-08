#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>


/* list structure */
struct list;

/* creates an empty list object */
struct list *createList();

/* adds a node to list l with key num to the front of the list */
void addFront(struct list *l, int num);

/* adds a node to list l with key num to the back of the list */
void addBack(struct list *l, int num);

/* removes the first node of a list and returns the key of the deleted node */
int deleteFront(struct list *l);

/* removes the last node of a list and returns the key of the deleted node */
int deleteBack(struct list *l);

/* prints out all the elements of the list */
void printlist(struct list *l);

/* deletes a list and free's it's memory */
int listDelete(struct list *l);

#endif /* LIST_H_ */