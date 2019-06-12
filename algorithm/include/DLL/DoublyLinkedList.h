#pragma once

typedef struct _Node {
	struct _Node *next;
	int data;
} Node;

typedef struct _List {
	Node* Head;
	Node* Tail;
}List;

void initList(List* list);
void test();