#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.hpp"
#include "../QUEUE/Queue.hpp" // queue�� �ʿ��ؼ�
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
	printf("DFS_adjmatrix\n");
	int i;
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			DFS_recur(G, V, i, check);
		}
	}
}

/* nrDFS_ajdmatrix
�������
*/
void nrDFS_ajdmatrix(int(*G)[MAX_VERTEX], int V, int* check) {
	printf("nrDFS_ajdmatrix\n");
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
	printf("DFS_adjlist\n");
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
	printf("nrDFS_adjlist\n");
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
���� ����� ����Ͽ� �ʺ�켱Ž���� �ǽ��ϴ� �Լ�
*/
void BFS_adjmatrix(int(*G)[MAX_VERTEX], int V, int *check) {
	printf("BFS_adjmatrix\n");
	int i, j;
	Queue queue(MAX_VERTEX);
	queue.init_queue();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			queue.put(i);
			check[i] = 1;
			while (queue.getSize() != 0) {
				i = queue.get();
				printf("%d-node visited\n", i);
				for (j = 0; j < V; j++) {
					if (G[i][j] != 0) {
						if (check[j] == 0) {
							queue.put(j);
							check[j] = 1;
						}
					}
				}
			}
		}
	}
}

/*
��������Ʈ�� ǥ���� �׷����� BFS������� Ž���ϴ� �Լ�
*/
void BFS_adjlist(node *G[], int V, int *check) {

	printf("BFS_adjlist\n");
	int i;
	node *t;
	Queue queue(MAX_VERTEX);
	queue.init_queue();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			queue.put(i);
			check[i] = 1;
			while (queue.getSize() != 0) {
				i = queue.get();
				printf("%d-node visited\n", i);
				for (t = G[i]; t != NULL; t = t->next) {
					int k = t->vertex;
					if (check[k] == 0) {
						queue.put(k);
						check[k] = 1;
					}
				}
			}
		}
	}
}

int  num_compo_adjmatix(int(*G)[MAX_VERTEX], int V, int *check) {
	int count = 0;
	int i, j;
	DQS stack(MAX_VERTEX);
	stack.init_stack();
	for (i = 0; i < V; i++)check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			printf("\n connected component %d : ", ++count);
			stack.push(i);
			check[i] = 1;
			while (stack.getSize() != 0) {
				i = stack.pop();
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

	return count;
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
	BFS_adjmatrix(G, V, check);

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

	int check[MAX_VERTEX] = {0, };
	DFS_adjlist(G, V, check);
	nrDFS_adjlist(G, V, check);
	BFS_adjlist(G, V, check);


	// �� �κп��� �� exception�� �߻��ϴ��� �����غ��ô�.
	// �ֿܰ� for������ ���ǿ� �ش��ϴ� �κ��� �� �����ؾ��Ѵ�.
	// i<V�� �����ϸ� �������� �۵��Ѵ�.
	// i<MAX_VERTEX�� �����ϸ� ���ܰ� �߻��Ѵ�.
	for (int i = 0; i < V; i++) {
		node* temp;
		for (temp = G[i]; temp != NULL; temp = temp->next) {
			printf("%d ", temp->vertex);
		}
		printf("\n");
	}
	return;
}