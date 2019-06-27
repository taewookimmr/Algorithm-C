#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.hpp"
#include "../QUEUE/Queue.hpp" // queue가 필요해서
#include "../DQS/DoubleQueueStack.hpp" // stack이 필요해서.


/*
array를 조건에 맞게 채우는 함수
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
		// out_of_array_index_exception은 발생 안하나?

	}

}

/*
list를 조건에 맞게 채우는 함수
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

/*
array 출력 함수
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
list 출력 함수
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


/*
char{A,B,C,D~}를 int{0,1,2,3~}로 변환해주는 함수
*/
int name2int(char c) {
	return c - 'A';
}

/*
 int{0,1,2,3~}를 char{A,B,C,D~}로 변환해주는 함수
*/
char int2name(int i) {
	return i + 'A';
}


/* DFS_recur, 190613 작성
인접행렬의 포인터 G와 정점의 수 V,
그리고 순회를 시작할 정점의 일련 번호를 인자로 받아서
i번째 정점에 연결된 연결 요소에 대해 순회한다.
check 배열도 받도록 수정하였다
*/
void DFS_recur(int(*G)[MAX_VERTEX], int V, int i, int* check) {
	int j = 0;
	check[i] = 1; // i번 정점을 방문하므로 표시한다.
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
DFS_adjlist 함수는 여러 개의 연결 요소로 구성된 그래프일 경우
방문되지 않은 연결 요소의 첫 정점을 찾아내어 DFS_recur함수를 호출하는 기능
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
비재귀판
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
인접리스트를 구성하는 한 연결요소를 dfs방식으로 순회하는 재귀함수
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

인접리스트를 구성하는 모든 연결요소를 순회하는 함수
재귀함수를 내부적으로 사용한다.
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
비재귀함수로서
인접리스트를 구성하는 모든 연결요소를 순회하는 함수
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
인접 행렬을 사용하여 너비우선탐색을 실시하는 함수
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
인접리스트로 표현된 그래프를 BFS방식으로 탐색하는 함수
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
(self-modifed version) save whether or not the node is articulating point.
 */
int AP_recur(node *G[], int i, int *check, int *order, int *son_of_root, int *isArti, int *mintop){
	
	node *t;
	int min, m;

	if (check[i] == 0) {
		check[i] = min = ++(*order);
		printf("%c-node start_%d \n", int2name(i), *son_of_root);
	}
	else {
		printf("%c-already checked\n", int2name(i));
		return mintop[i];
	}

	int roopCount = 0;
	for(t = G[i]; t->next != NULL; t = t->next){
		roopCount++;
		if(i == 0 && check[t->vertex] == 0) ++(*son_of_root);

		if(check[t->vertex] == 0){
			m = AP_recur(G, t->vertex, check, order, son_of_root, isArti, mintop); // DFS-like
			if(m <= min){
				min = m; // pointing the most highest(ancestor)
			}
			if( m >= check[i] && i != 0){
				isArti[i] = 1;
			}else{
				isArti[i] = 0;
			}
		}else{
			if(check[t->vertex] < min){
				min = check[t->vertex];
			}
		}
	}
	if (roopCount == 0) isArti[i] = 1;
	mintop[i] = min;
	return min;
}

/*

*/
void AP_search(node* G[], int V, int* check, int* order, int* son_of_root, int* isArti, int* mintop) {
	int i;
	
	for (i = 0; i < V; i++) {
		check[i] = 0;
		isArti[i] = -1;
		mintop[i] = 0;
	}

	for(i = 0 ; i < V; i++)
		AP_recur(G, i, check, order, son_of_root, isArti, mintop);


	if (*son_of_root > 1) {
		isArti[0] = 1;
	}
	else {
		isArti[0] = 0;
	}


	for (i = 0; i < V; i++) {

		if (isArti[i] == 1) {
			printf("%c-node is articulating point.\n", int2name(i));
		}
		else {
			printf("%c-node is not arti. point.\n", int2name(i));
		}
	}

	printf("search order : ");
	for (i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (check[j] - 1 == i ) {
				printf("%c ", int2name(j));
				break;
			}
		}
	}

	printf("\nmintop  : \n");
	for (i = 0; i < V; i++) {
		printf("%c : %d\n", int2name(i), mintop[i]);
	}



	return;
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


	// 이 부분에서 왜 exception이 발생하는지 생각해봅시다.
	// 최외각 for문에서 조건에 해당하는 부분을 잘 설정해야한다.
	// i<V로 설정하면 문제없이 작동한다.
	// i<MAX_VERTEX로 설정하면 예외가 발생한다.
	for (int i = 0; i < V; i++) {
		node* temp;
		for (temp = G[i]; temp != NULL; temp = temp->next) {
			printf("%c ", int2name(temp->vertex));
		}
		printf("\n");
	}


	int myOrder = 0;
	int mySon = 0;
	int* order = &myOrder;
	int* son = &mySon;
	int* checkit = (int*)malloc(sizeof(int) * V);
	int* isArti = (int*)malloc(sizeof(int) * V);
	int* mintop = (int*)malloc(sizeof(int) * V);

	AP_search(G, V, checkit, order, son, isArti, mintop);

	return;
}