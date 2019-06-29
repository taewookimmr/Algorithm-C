#pragma once

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#ifndef MAX_VERTEX
	#define MAX_VERTEX 100
#endif // !MAX_VERTEX

#define UNSEEN (-INT_MAX)

typedef struct _node {
	struct _node* next;
	int vertex;
	int weight;
} node;


FILE* fp;
node* G_list[MAX_VERTEX];
int check[MAX_VERTEX];
int parent[MAX_VERTEX];
int nheap = 0;
int heap[MAX_VERTEX];

void upheap(int heap[], int k);
void downheap(int heap[], int l);
void adjust_heap(int heap[], int n);
void print_heap(int heap[]);

int pq_update(int h[], int v, int p);
void pq_init();
int pq_empty();
int pq_extract(int heap[]);

int name2int(char c);
int int2name(int i);

void input_adjlist(node* G[], int* V, int* E);
void print_adjlist(node* G[], int V);

void print_tree(int tree[], int n);
void print_cost(int check[], int n);
void visit(int index);

void PFS_adjlist(node* G[], int V);
