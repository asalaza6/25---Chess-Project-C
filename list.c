/*
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int p_dest;
    int p_from;
    struct node * next;
} NODE;

NODE* initializeNode(int from, int dest){
    NODE* head = (NODE *) malloc(sizeof(NODE));
    head->p_from = from;
    head->p_dest = dest;
    return head;
}
void print_list(NODE *head){
    NODE * current = head;
    while (current != NULL) {
        printf("%d -> %d\n", current->p_from, current-> p_dest);
        current = current->next;
    }
}

void PushBack(NODE *head, int from, int dest) {
    NODE * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (NODE *) malloc(sizeof(NODE));
    current->next->p_from = from;
    current->next->p_dest = dest;
    current->next->next = NULL;
}

void PushFront(NODE *head, int from, int dest) {
    NODE * new_node;
    new_node = (NODE *) malloc(sizeof(NODE));
    new_node->p_dest = dest;
    new_node->p_from = from;
    new_node->next = head;
    head = new_node;
}

void removeAll(NODE** head) 
{ 
   NODE* current = *head; 
   NODE* next; 
  
   while (current != NULL)  
   { 
       
       next = current->next; 
       free(current); 
       current = next; 
   } 
    
   *head = NULL; 
} 


*/