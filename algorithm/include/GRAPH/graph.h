#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_VERTEX 100
typedef struct _node {
	struct _node *next;
	int vertex;
} node;
void input_adjmatrix(int(*arr)[MAX_VERTEX], int *v, int *e, FILE *fp);
void input_adjlist(node *arr[], int *v, int *e, FILE *fp);
void print_adjmatrix(int (*G)[MAX_VERTEX], int *V);
int  name2int(char c);
char int2name(int i);


void Main_graph(int argc, char *argv[], int(*G)[MAX_VERTEX], FILE *fp);