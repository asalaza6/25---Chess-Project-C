#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
//#include "Game.h"
typedef struct node {
    int p_dest;
    int p_from;
    struct node * next;
} NODE;
void PushBack(NODE *head, int from, int dest) ;
void print_list(NODE *head);
NODE* initializeNode(int from, int dest);

void PushFront(NODE *head, int from, int dest);

void removeAll(NODE** head);

#endif