#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.hpp"
#include "../DQS/DoubleQueueStack.hpp" // stack�� �ʿ��ؼ�.


/*
array�� ���ǿ� �°� ä��� �Լ�
*/
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
		// out_of_array_index_exception�� �߻� ���ϳ�?

	}

}

/*
list�� ���ǿ� �°� ä��� �Լ�
*/
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

		//���� �׷����� ��Ī���� ǥ���ϱ� ����
		i = name2int(vertex[1]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->next = G[i];
		G[i] = t;
	}

	// free(t); 
	// ���� free(t)�� �����ϸ� 
	// print_adjlist ���ۿ� ������ ��ģ��. 
	// ��? ���ǰ� �ִ� �����̴ϱ�!

	
}

/*
array ��� �Լ�
*/
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


/*
list ��� �Լ�
*/
void print_adjlist(node *G[], int *V) {
	int size = *V;
	int i = 0, j = 0, k = 0;

	node* temp = NULL;
	int *condition = NULL;
	condition = (int*)malloc(sizeof(int)*size);

	for (i = 0; i < size; i++) {
		
		temp = G[i];
	
		for (k = 0; k < size; k++) {
			condition[k] = 0; 	// condition �迭 �ʱ�ȭ
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


/*
char{A,B,C,D~}�� int{0,1,2,3~}�� ��ȯ���ִ� �Լ�
*/
int name2int(char c) {
	return c - 'A';
}

/*
 int{0,1,2,3~}�� char{A,B,C,D~}�� ��ȯ���ִ� �Լ�
*/
char int2name(int i) {
	return i + 'A';
}


/* DFS_recur, 190613 �ۼ�
��������� ������ G�� ������ �� V,
�׸��� ��ȸ�� ������ ������ �Ϸ� ��ȣ�� ���ڷ� �޾Ƽ�
i��° ������ ����� ���� ��ҿ� ���� ��ȸ�Ѵ�.
check �迭�� �޵��� �����Ͽ���
*/
void DFS_recur(int(*G)[MAX_VERTEX], int V, int i, int* check) {
	int j = 0;
	check[i] = 1; // i�� ������ �湮�ϹǷ� ǥ���Ѵ�.
	printf("%d-node visited\n", i);
	for (j = 0; j < V; j++) {
		if (G[i][j] != 0) {
			if (check[j] == 0) {
				DFS_recur(G, V, j, check);
			}
		}
	}
}

/* DFS_adjmatrix
DFS_adjlist �Լ��� ���� ���� ���� ��ҷ� ������ �׷����� ���
�湮���� ���� ���� ����� ù ������ ã�Ƴ��� DFS_recur�Լ��� ȣ���ϴ� ���
*/
void DFS_adjmatrix(int(*G)[MAX_VERTEX], int V, int* check) {
	int i;
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			DFS_recur(G, V, i, check);
		}
		printf("---���� ��� ���м�---\n");
	}
}

/* nrDFS_ajdmatrix
�������
*/
void nrDFS_ajdmatrix(int(*G)[MAX_VERTEX], int V, int* check) {
	int i, j;
	
	DQS stack(MAX_VERTEX);
	stack.init_stack();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			stack.push(i);
			check[i] = 1;
			while (stack.getSize()) {
				i = stack.pop();
				printf("%d-node visited\n", i);
				for (j = 0; j < V; j++) {
					if (G[i][j] != 0) {
						if (check[j] == 0) {
							stack.push(j);
							check[j] = 1;
						}
					}
				}
			}
		}
	}

	
}

/*
��������Ʈ�� �����ϴ� �� �����Ҹ� dfs������� ��ȸ�ϴ� ����Լ�
*/
void DFS_recur_list(node *G[], int V, int i, int* check) {
	node *t;
	check[i] = 1;
	printf("%d-node visited\n", i);
	for (t = G[i]; t != NULL; t= t->next) {
		int j = t->vertex;
		if (check[j] == 0) {
			DFS_recur_list(G, V, j, check);
		}
	}
}

/*

��������Ʈ�� �����ϴ� ��� �����Ҹ� ��ȸ�ϴ� �Լ�
����Լ��� ���������� ����Ѵ�.
*/
void DFS_adjlist(node *G[], int V, int* check) {
	int i;
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			DFS_recur_list(G, V, i, check);
		}
	}
}
/*
������Լ��μ�
��������Ʈ�� �����ϴ� ��� �����Ҹ� ��ȸ�ϴ� �Լ�
*/
void nrDFS_adjlist(node *G[], int V, int* check) {
	int i;
	node *t;
	DQS stack(MAX_VERTEX);
	stack.init_stack();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			stack.push(i);
			check[i] = 1;
			while (stack.getSize()) {
				i = stack.pop();
				printf("%d-node visited\n", i);
				for (t = G[i]; t != NULL; t = t->next) {
					int j = t->vertex;
					if (check[j] == 0) {
						stack.push(j);
						check[j] = 1;
					}
				}
			}
		}
	}
}



/*
array expression test
*/
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


	int check[MAX_VERTEX] = {0, };
	DFS_adjmatrix(G, V, check);
	nrDFS_ajdmatrix(G, V, check);

	return;
}


/*
list expression test
*/
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

	int check[MAX_VERTEX] = { 0, };
	DFS_adjlist(G, V, check);
	nrDFS_adjlist(G, V, check);

	printf("what the fuck\n");
	for (int i = 0; i < MAX_VERTEX; i++) {
		node* temp;
		for (temp = G[i]; temp != NULL; temp = temp->next) {
			printf("%d ", temp->vertex);
		}
		printf("\n");

	}
	return;
}