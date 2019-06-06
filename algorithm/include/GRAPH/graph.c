#include "graph.h"


// 인접배열법을 사용
void input_adjmatrix(int(*arr)[MAX_VERTEX], int *v, int *e, FILE *fp) {
	char vertex[3];
	int i, j, k;
	printf("\nInput number of Vertex & Edge\n");
	fscanf(fp, "%d %d", v, e);
	for (i = 0; i < *v; i++)
		for (j = 0; j < *v; j++)
			arr[i][j] = 0;

	for (i = 0; i < *v; i++)
		arr[i][i] = 1; // assumption of reflexive node

	for (k = 0; k < *e; k++) {
		if(fp == stdin)
			printf("\nInput two Vertex consist of Edge ->");
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		arr[i][j] = 1;
		arr[j][i] = 1;
		// out_of_array_index_exception은 발생 안하나?

	}

}

void input_adjlist(node *arr[], int *v, int *e, FILE *fp) {

	char vertex[3];
	int i, j;
	node *t;
	print("\nInput number of Vertex & Edge\n");
	fscanf(fp, "%d %d", v, e);
	for (i = 0; i < *v; i++)
		arr[i] = NULL;
	for (j = 0; j < *e; j++) {
		print("\nInput two Vertex consist of Edge-->");
		fscanf(fp, "%s", vertex);

		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = arr[i];
		arr[i] = t;

		//무향 그래프의 대칭성을 표현하기 위해
		i = name2int(vertex[1]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);

	}
	
}

void print_adjmatrix(int(*G)[MAX_VERTEX], int *V) {
	int size = *V;
	int i = 0, j = 0;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%2d", G[i][j]);
		}
		printf("\n");
	}
}

int name2int(char c) {
	return c - 'A';
}

char int2name(int i) {
	return i + 'A';
}

void Main_graph(int argc, char *argv[], int (*G)[MAX_VERTEX], FILE *fp) {
	
	int V, E;
	if (argc < 2)
		fp = stdin;
	else
		if ((fp = fopen(argv[1], "rt")) == NULL) {
			printf("\nThat file does not exist !");
			exit(1);
		}

	input_adjmatrix(G, &V, &E, fp);
	printf("\n\nAdjacency Matrix representation for graph\n");
	print_adjmatrix(G, &V);

	return;
}