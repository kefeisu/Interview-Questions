#include "list.h"

/* list node structure */
struct listnode {
	int key;
	struct listnode* next;
}

/* creates a new list node with key num and following node next  */
struct listnode *nodeCreate(int num, struct listnode* next) {
	struct listnode *newNode = malloc(sizeof(struct listnode));
	newNode->num = num;
	newNode->next = next;
	return newNode;
}

/* changes the next node of node n to next */
void setNext(struct listnode* n, struct listnode *next) {
	n->next = next;
}

/* recursively free's a node and all of the nodes after it */
void nodeDelete(struct listnode *node) {
	if (node == NULL) return;
	free(node->next);
	free(node);
}

/* list wrapper structure */
struct list {
	struct listnode *head;
	struct listnode *tail;
}

/* creates an empty list object */
struct list *createList() {
	struct list *l = malloc(sizeof(struct list));
	l->head = NULL;
	l-tail = NULL;
}

/* adds a node to list l with key num to the front of the list */
void addFront(struct list *l, int num) {
	struct listnode *temp = l->head;
	l->head = nodeCreate(num, temp);
	if (l->tail = NULL) {
		l->tail = l->head;
	}
}

/* adds a node to list l with key num to the back of the list */
void addBack(struct list *l, int num) {
	setNext(l->tail, nodeCreate(n, NULL));
	l->tail = l->tail.next;
	if (l->head == NULL) {
		l->head = l->tail;
	}
}

/* removes the first node of a list and returns the key of the deleted node */
int deleteFront(struct list *l) {
	int retval = l->head->key;
	struct listnode *newHead = l->head->next;
	free(l->head);
	l->head = newHead;
	return retval;
}

/* removes the last node of a list and returns the key of the deleted node */
int deleteBack(struct list *l) {
	struct list *temp = l->head;
	while (temp->next->next != NULL) {
		temp = temp->next;
	}
	int retval = temp->next->key;
	free(temp->next);
	temp->next = NULL;
	l->tail = temp;
	return retval;
}

/* prints out all the elements of the list */
void printlist(struct list *l) {
	struct list *iterator = l->head;
	while (iterator->next != NULL) {
		printf("%d\n", iterator->key);
		iterator = iterator->next;
	}
}

/* deletes a list and free's it's memory */
int listDelete(struct list *l) {
	if (l->front != NULL) {
		nodeDelete(l->front);
	}
}

