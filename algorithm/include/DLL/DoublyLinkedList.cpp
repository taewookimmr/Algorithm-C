#include "DoublyLinkedList.h"
#include <stdlib.h>
#include <iostream>

void initList(List *list) {
	list->Head = NULL;
	list->Tail = NULL;
}

void test() {

	int numOfTestNodes = 5;
	int indexOfDeletedNode[] = {1,3};

	List *myList = (List*)malloc(sizeof(List));
	initList(myList);

	Node ** nodes = (Node**)malloc(sizeof(Node*)*numOfTestNodes);
	for (int i = 0; i < numOfTestNodes; i++) {
		nodes[i] = (Node *)malloc(sizeof(Node));
		nodes[i]->data = i;
	}

	myList->Head = nodes[0];
	Node* pres = myList->Head;

	for (int i = 1; i < numOfTestNodes; i++) {
		pres->next = nodes[i];
		pres = pres->next;
	}
	// ������ ������ pres�� ������ ��带 ����Ű�� �ִ�.
	myList->Tail = pres;

	Tester<List*, int> tester((VaFunc_t)RemoveNodeFromList, "��������׽�Ʈ", 10);
	
	tester.TestRegisteredFunc(0, myList, indexOfDeletedNode[0]);
	tester.TestRegisteredFunc(0, myList, indexOfDeletedNode[1]-1);

	tester.DataChecker((int)myList->Head, (int)nodes[0]);

	tester.DataChecker((int)myList->Head->Next, (int)nodes[2]);
	tester.DataChecker((int)nodes[2]->Prev, (int)myList->Head);

	tester.DataChecker((int)nodes[2]->Next, (int)myList->Tail);
	tester.DataChecker((int)nodes[2], (int)myList->Tail->Prev);

	tester.DataChecker((int)myList->Tail, (int)nodes[4]);

	tester.DataChecker((int)myList->Head->Prev, (int)NULL);
	tester.DataChecker((int)myList->Tail->Next, (int)NULL);

	DestroyList(myList);
	free(nodes);

	tester.MemoryLeakChecker();
}

void test2() {

	int numOfInitialNodes = 7;
	int indexOfDeletedNode[] = {0, 6, 2, 4}; // initial index�� �ش���.
	int indexChange[4] = {0, };
	int fin_indexOfDeletedNode[4] = {0, };

	int numOfDeletedNodes = sizeof(indexOfDeletedNode) / sizeof(int);

	for (int i = 1; i < numOfDeletedNodes; i++) {
		for (int j = 0; j < i; j++) {
			if (indexOfDeletedNode[j] < indexOfDeletedNode[i])
				indexChange[i]++;
		}
		fin_indexOfDeletedNode[i] = indexOfDeletedNode[i] - indexChange[i];
	}


	// ��������׽�Ʈ�� ����� ���̸���Ʈ�� �غ����
	List *myList = (List*)malloc(sizeof(List));
	initList(myList);

	Node ** nodes = (Node**)malloc(sizeof(Node*)*numOfInitialNodes);
	// �׽�Ʈ���� �������� ���� nodes[i]�� ���� free�ؾ� �Ѵ�.
	// �׸��� nodes ���������ʹ� ���߿� free�ؾ� �Ѵ�.

	for (int i = 0; i < numOfInitialNodes; i++) {
		nodes[i] = (Node *)malloc(sizeof(Node));
		nodes[i]->data = i;
	}

	myList->Head = nodes[0];
	Node* pres = myList->Head;

	for (int i = 1; i < numOfInitialNodes; i++) {
		pres->next = nodes[i];
		pres = pres->next;
	}
	
	myList->Tail = pres; // ������ ������ pres�� ������ ��带 ����Ű�� �ִ�.
	// ��������׽�Ʈ�� ����� ���̸���Ʈ�� �غ�Ϸ�
	
	int numOfTest = (numOfInitialNodes - numOfDeletedNodes -1) * 2  + 2;
	Tester<List*, int> tester((VaFunc_t)RemoveNodeFromList, "��������׽�Ʈ", numOfTest);

	for (int i = 0; i < numOfDeletedNodes; i++) {
		tester.TestRegisteredFunc(0, myList, fin_indexOfDeletedNode[i]);
	}

	tester.DataChecker((int)myList->Head->Prev, (int)NULL);
	tester.DataChecker((int)myList->Head, (int)nodes[1]);

	tester.DataChecker((int)nodes[3]->Prev, (int)myList->Head);
	tester.DataChecker((int)myList->Head->Next, (int)nodes[3]);

	tester.DataChecker((int)myList->Tail->Prev, (int)nodes[3]);
	tester.DataChecker((int)nodes[3]->Next, (int)myList->Tail);

	tester.DataChecker((int)myList->Tail->Next, (int)NULL);
	tester.DataChecker((int)myList->Tail, (int)nodes[5]);

	DestroyList(myList);
	free(nodes);

	tester.MemoryLeakChecker();
}

int main() {
	test2();
}