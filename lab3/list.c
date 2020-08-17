#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode *link;
} ListNode;

void error(const char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1); 
}

ListNode *create_node(element data, ListNode *link) {
	ListNode *new_node; new_node = (ListNode *)malloc(sizeof(ListNode));
	if (new_node == NULL)
		error("malloc err");
	new_node->data = data;
	new_node->link = link;
	return (new_node); 
}

void insert_node(ListNode **phead, ListNode *p, ListNode *new_node) {
	if (*phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) {
		new_node->link = *phead;
		*phead = new_node;
	}
	else {
		new_node->link = p->link;
		p->link = new_node;
	} 
}

void display(ListNode *head) {
	ListNode *p = head;
	while (p != NULL) {
		printf("%d->", p->data);
		p = p->link;
	}
	printf("\n");
}

ListNode *search(ListNode *head, int x) {
	ListNode *p;
	p = head;
	while (p != NULL) {
		if (p->data == x)
			return p;
		p = p->link;
	}
	return p;
}

void remove_node(ListNode **phead, ListNode *p, ListNode *removed) {
	if (p == NULL)
		*phead = (*phead)->link;
	else
		p->link = removed->link;

	free(removed);
}


int main() {
	ListNode *list1 = NULL;
	insert_node(&list1, NULL, create_node(10, NULL));
	insert_node(&list1, NULL, create_node(20, NULL));
	insert_node(&list1, NULL, create_node(30, NULL));
	display(list1);

	remove_node(&list1, NULL, list1);
	display(list1);

	return 0;
}