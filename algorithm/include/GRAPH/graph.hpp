#pragma once

#include <stdio.h>
#define MAX_VERTEX 100

typedef struct _node {
	struct _node *next;
	int vertex;
} node;

void input_adjmatrix(int(*arr)[MAX_VERTEX], int *v, int *e, FILE *fp);
void input_adjlist(node *arr[], int *v, int *e, FILE *fp);
void print_adjmatrix(int (*G)[MAX_VERTEX], int *V);
void print_adjlist(node *G[], int *V);
int  name2int(char c);
char int2name(int i);


void DFS_recur(int(*G)[MAX_VERTEX], int V, int i, int* check); 
void DFS_adjmatrix(int(*G)[MAX_VERTEX], int V, int* check);
void nrDFS_ajdmatrix(int(*G)[MAX_VERTEX], int V, int* check);

void DFS_recur_list(node *G[], int V, int i, int* check);
void DFS_adjlist(node *G[], int V, int* check);
void nrDFS_adjlist(node *G[], int V, int* check);


void Main_graph(int argc, char *argv[], int(*G)[MAX_VERTEX], FILE *fp);
void Main_graph_list(int argc, char *argv[], node *G[], FILE *fp);