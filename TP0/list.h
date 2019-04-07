#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct node {
	int val;
	struct node* next;
} Node;

typedef struct {
	int size;
	Node* head;
	Node* tail;
} List;


// tamanho da lista
int size(List);

// valor da celula
int val(Node);

// lista vazia
List new_list();

// coloca valor no final da lista
void append(List*, int);

// primeira celula da lista
Node first(List);

// proxima celula da lista
Node next(Node);

// apaga celulas recursivamente
void del_node(Node*);

// apaga lista
void del(List*);


#endif
