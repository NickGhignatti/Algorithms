#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List *list_create(void) {
	List *L = malloc(sizeof(List));
	if (L == NULL) {
		fprintf(stderr, "Errore nella creazione della lista\n");
		exit(EXIT_FAILURE);
	}
	L->sentinel.succ = &(L->sentinel);
	L->sentinel.pred = &(L->sentinel);
	L->length = 0;
	return L;
}

int list_length(const List *L) {
	return L->length;
}

void list_clear(List *L){
	ListNode *temp = list_last(L);
	while(temp != &L->sentinel){
		temp = temp->pred;
		free(temp->succ);
	}
	L->sentinel.succ = &(L->sentinel);
	L->sentinel.pred = &(L->sentinel);
	L->length = 0;
}

void list_destroy(List *L){
	list_clear(L);
	free(L);
}

int list_is_empty(const List *L){
	return L->length == 0 ? 1 : 0;
}

ListNode *list_search(const List *L, ListInfo k){
	ListNode *temp = list_first(L);
	while(temp != &L->sentinel){
		if(temp->val == k)
			return temp;
		temp = temp->succ;
	}
	return temp;
}

ListNode *list_first(const List *L) {
	return L->sentinel.succ;
}

ListNode *list_last(const List *L) {
	return L->sentinel.pred;
}

void list_add_first(List *L, ListInfo k) {
	ListNode *temp = list_first(L);
	ListNode *newNode = malloc(sizeof(ListNode));
	newNode->val = k;
	newNode->pred = &L->sentinel;
	newNode->succ = temp;
	L->sentinel.succ = newNode;
	temp->pred = newNode;
}

void list_add_last(List *L, ListInfo k) {
	ListNode *temp = list_last(L);
	ListNode *newNode = malloc(sizeof(ListNode));
	newNode->val = k;
	newNode->succ = &L->sentinel;
	newNode->pred = temp;
	L->sentinel.pred = newNode;
	temp->succ = newNode;
}

void list_remove(List *L, ListNode *n) {
	ListNode *temp = list_first(L);
	while (temp != &L->sentinel) {
		if (temp == n){
			(temp->pred)->succ = (temp->succ)->pred;
			free(temp);
			break;
		}
		temp = temp->succ;
	}
	return temp;
}

ListInfo list_remove_first(List *L) {
	ListNode *temp = list_first(L);
	temp = temp->succ;
	L->sentinel.succ = temp;
	temp->pred = &L->sentinel;
	free(temp->pred);
}

ListInfo list_remove_last(List *L) {
	ListNode *temp = list_last(L);
	temp = temp->pred;
	L->sentinel.pred = temp;
	temp->succ = &L->sentinel;
	free(temp->succ);
}

ListNode *list_succ(const ListNode *n) {
	return n->succ;
}

ListNode *list_pred(const ListNode *n) {
	return n->pred;
}

ListNode *list_nth_element(const List *L, int n) {
	if(n < 0 || n >= list_length(L))
		return &(L->sentinel);
	ListNode *temp = list_first(L);
	while(n > 0){
		temp = temp->succ;
	}
	return temp;
}

void list_concat(List *L1, List *L2) {
	ListNode *temp = list_last(L2);
	L2->sentinel.pred = L1->sentinel.pred;
	temp->succ = L1->sentinel.succ;
	list_clear(L1);
}

int list_equal(const List *L1, const List *L2){
	int l1 = list_length(L1), l2 = list_length(L2);
	if(l1 != l2)
		return 0;
	int i = 0;
	ListNode *n1 = &L1->sentinel.succ, *n2 = &L2->sentinel.succ;
	for(i; i < l1; i++) {
		if(n1->val != n2->val)
			return 0;
		n1 = n1->succ;
		n2 = n2->succ;
	}
	return 1;
}

void list_print(const List *L) {
    ListNode *node;
    for (node = list_first(L); node != list_end(L); node = list_succ(node)) {
        printf("%d ", node->val);
    }
    printf("\n");
}

const ListNode *list_end(const List *L) {
	return &L->sentinel;
}