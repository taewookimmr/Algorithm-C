#include "graph.h"


// 인접배열법을 사용
void input_adjmatrix(int(*G)[MAX_VERTEX], int *v, int *e, FILE *fp) {
	char vertex[3];
	int i, j, k;
	printf("\nInput number of Vertex & Edge\n");
	fscanf(fp, "%d %d", v, e);
	for (i = 0; i < *v; i++)
		for (j = 0; j < *v; j++)
			G[i][j] = 0;

	for (i = 0; i < *v; i++)
		G[i][i] = 1; // assumption of reflexive node

	for (k = 0; k < *e; k++) {
		if(fp == stdin)
			printf("\nInput two Vertex consist of Edge ->");
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		G[i][j] = 1;
		G[j][i] = 1;
		// out_of_array_index_exception은 발생 안하나?

	}

}

void input_adjlist(node *G[], int *v, int *e, FILE *fp) {

	char vertex[3];
	int i, j;

	node *t = NULL;
	printf("\nInput number of Vertex & Edge\n");
	fscanf(fp, "%d %d", v, e);

	for (i = 0; i < *v; i++) {
		G[i] = (node*)malloc(sizeof(node));
		G[i]->vertex = i;
		G[i]->next = NULL;
	}
		
	for (j = 0; j < *e; j++) {
		printf("\nInput two Vertex consist of Edge-->");
		fscanf(fp, "%s", vertex);

		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = G[i];
		G[i] = t;

		//무향 그래프의 대칭성을 표현하기 위해
		i = name2int(vertex[1]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->next = G[i];
		G[i] = t;
	}

	// free(t); 
	// 위의 free(t)를 실행하면 
	// print_adjlist 동작에 영향을 끼친다. 
	// 왜? 사용되고 있는 공간이니까!

	
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

void print_adjlist(node *G[], int *V) {
	int size = *V;
	int i = 0, j = 0, k = 0;

	node* temp = NULL;
	int *condition = NULL;
	condition = (int*)malloc(sizeof(int)*size);

	for (i = 0; i < size; i++) {
		
		temp = G[i];
	
		for (k = 0; k < size; k++) {
			condition[k] = 0; 	// condition 배열 초기화
		}

		while (temp != NULL) {
			condition[temp->vertex] = 1;
			temp = temp->next;
		}

		for (j = 0; j < size; j++) {
			if (condition[j])
				printf("%2d", 1);
			else
				printf("%2d", 0);
		}
		printf("\n");
	}

	free(temp);
	free(condition);
}

int name2int(char c) {
	return c - 'A';
}

char int2name(int i) {
	return i + 'A';
}


void DFS_recur(int(*G)[MAX_VERTEX], int V, int i, int* check) {
	int j = 0;
	check[i] = 1; // i번 정점을 방문하므로 표시한다.
	print("%d-node visited\n", i);
	for (j = 0; j < V; j++) {
		if (G[i][j] != 0) {
			if (check[j] == 0) {
				DFS_recur(G, V, i, check);
			}
		}
	}
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

void Main_graph_list(int argc, char *argv[], node *G[], FILE *fp) {

	int V, E;
	if (argc < 2)
		fp = stdin;
	else
		if ((fp = fopen(argv[1], "rt")) == NULL) {
			printf("\nThat file does not exist !");
			exit(1);
		}

	input_adjlist(G, &V, &E, fp);
	printf("\n\nAdjacency Matrix representation for graph\n");
	print_adjlist(G, &V);

	return;
}