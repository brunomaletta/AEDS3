#include "list.h"

int size(List L) {
	return L.size;
}

int val(Node N) {
	return N.val;
}

List new_list() {
	List L;
	L.size = 0;
	L.head = (Node*) malloc(sizeof(Node));
	L.tail = L.head;
	L.head->next = NULL;
	return L;
}

void append(List* L, int val) {
	Node* N = (Node*) malloc(sizeof(Node));
	L->tail->next = N;
	L->tail = N;
	N->val = val;
	N->next = NULL;
	L->size++;
}

Node first(List L) {
	return *(L.head->next);
}

Node next(Node N) {
	if (N.next == NULL) return N;
	return *(N.next);
}

void del_node(Node* N) {
	if (N == NULL) return;

	del_node(N->next);
	free(N);
}

void del(List* L) {
	del_node(L->head);
}
