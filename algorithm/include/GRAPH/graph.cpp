#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "Graph.hpp"
#include "../QUEUE/Queue.hpp" // queue가 필요해서
#include "../DQS/DoubleQueueStack.hpp" // stack이 필요해서.

namespace Graph {

	FILE* fp;
	int G_array[MAX_VERTEX][MAX_VERTEX];
	node* G[MAX_VERTEX];
	int check[MAX_VERTEX];
	int order[MAX_VERTEX];
	int son_of_root[MAX_VERTEX]; 
	int isArti[MAX_VERTEX];
	int mintop[MAX_VERTEX];

	/*
	array를 조건에 맞게 채우는 함수
	*/
	void input_adjmatrix(int(*G)[MAX_VERTEX], int *v, int *e) {
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
	void input_adjlist(node *G[], int *v, int *e) {

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
	void DFS_recur(int(*G)[MAX_VERTEX], int V, int i) {
		int j = 0;
		check[i] = 1; // i번 정점을 방문하므로 표시한다.
		printf("%d-node visited\n", i);
		for (j = 0; j < V; j++) {
			if (G[i][j] != 0) {
				if (check[j] == 0) {
					DFS_recur(G, V, j);
				}
			}
		}
	}

	/* DFS_adjmatrix
	DFS_adjlist 함수는 여러 개의 연결 요소로 구성된 그래프일 경우
	방문되지 않은 연결 요소의 첫 정점을 찾아내어 DFS_recur함수를 호출하는 기능
	*/
	void DFS_adjmatrix(int(*G)[MAX_VERTEX], int V) {
		printf("DFS_adjmatrix\n");
		int i;
		for (i = 0; i < V; i++) check[i] = 0;
		for (i = 0; i < V; i++) {
			if (check[i] == 0) {
				DFS_recur(G, V, i);
			}
		}
	}

	/* nrDFS_ajdmatrix
	비재귀판
	*/
	void nrDFS_ajdmatrix(int(*G)[MAX_VERTEX], int V) {
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
	void DFS_recur_list(node *G[], int V, int i) {
		node *t;
		check[i] = 1;
		printf("%d-node visited\n", i);
		for (t = G[i]; t != NULL; t= t->next) {
			int j = t->vertex;
			if (check[j] == 0) {
				DFS_recur_list(G, V, j);
			}
		}
	}

	/*

	인접리스트를 구성하는 모든 연결요소를 순회하는 함수
	재귀함수를 내부적으로 사용한다.
	*/
	void DFS_adjlist(node *G[], int V) {
		printf("DFS_adjlist\n");
		int i;
		for (i = 0; i < V; i++) check[i] = 0;
		for (i = 0; i < V; i++) {
			if (check[i] == 0) {
				DFS_recur_list(G, V, i);
			}
		}
	}
	/*
	비재귀함수로서
	인접리스트를 구성하는 모든 연결요소를 순회하는 함수
	*/
	void nrDFS_adjlist(node *G[], int V) {
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
	void BFS_adjmatrix(int(*G)[MAX_VERTEX], int V) {
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
	void BFS_adjlist(node *G[], int V) {

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

	int  num_compo_adjmatix(int(*G)[MAX_VERTEX], int V) {
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
	int AP_recur(node *G[], int i){
	
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

		int loopCount = 0;
		for(t = G[i]; t->next != NULL; t = t->next){
			loopCount++;
			if(i == 0 && check[t->vertex] == 0) ++(*son_of_root);

			if(check[t->vertex] == 0){
				m = AP_recur(G, t->vertex); // DFS-like
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
		if (loopCount == 0) isArti[i] = 1;
		mintop[i] = min;
		return min;
	}

	/*

	*/
	void AP_search(node* G[], int V) {
		int i;
	
		for (i = 0; i < V; i++) {
			check[i] = 0;
			isArti[i] = -1;
			mintop[i] = 0;
		}

		for(i = 0 ; i < V; i++)
			AP_recur(G, i);


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
	void Main_graph(int argc, char *argv[]) {
	
		int V, E;
		if (argc < 2)
			fp = stdin;
		else
			if ((fp = fopen(argv[1], "rt")) == NULL) {
				printf("\nThat file does not exist !");
				exit(1);
			}

		input_adjmatrix(G_array, &V, &E);
		printf("\n\nAdjacency Matrix representation for graph\n");
		print_adjmatrix(G_array, &V);


		int check[MAX_VERTEX] = {0, };
		DFS_adjmatrix(G_array, V);
		nrDFS_ajdmatrix(G_array, V);
		BFS_adjmatrix(G_array, V);

		return;
	}

	/*
	list expression test
	*/
	void Main_graph_list(int argc, char *argv[]) {

		int V, E;
		if (argc < 2)
			fp = stdin;
		else
			if ((fp = fopen(argv[1], "rt")) == NULL) {
				printf("\nThat file does not exist !");
				exit(1);
			}

		input_adjlist(G, &V, &E);
		printf("\n\nAdjacency Matrix representation for graph\n");
		print_adjlist(G, &V);

		int check[MAX_VERTEX] = {0, };
		DFS_adjlist(G, V);
		nrDFS_adjlist(G, V);
		BFS_adjlist(G, V);


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

		AP_search(G, V);

		return;
	}


} // end of namespace Graph

namespace WeightGraph {

	namespace PFS {
		FILE* fp;
		int G_matrix[MAX_VERTEX][MAX_VERTEX];
		node* G_list[MAX_VERTEX];
		node* G_spp[MAX_VERTEX]; // 최단 경로를 저장하는 노드 포인터 배열
		int check[MAX_VERTEX];
		int parent[MAX_VERTEX];
		int nheap = 0;
		int heap[MAX_VERTEX];

		int distance_dijkstra[MAX_VERTEX];

		/*
			indirect upheap
		*/
		void upheap(int heap[], int k) {
			int v;
			v = heap[k];
			while (check[heap[k / 2]] <= check[v] && k / 2 > 0) {

				heap[k] = heap[k / 2];
				k /= 2;
			}
			heap[k] = v;
		}

		/*
			descend the k-th node to appropriate position
		*/
		void downheap(int heap[], int k) {
			int i, v;
			v = heap[k];
			while (k <= nheap / 2) {
				// only internal node
				i = k << 1;
				if (i < nheap && check[heap[i]] < check[heap[i + 1]]) i++;
				if (check[v] >= check[heap[i]]) break;
				heap[k] = heap[i];
				k = i;
			}
			heap[k] = v;
		}

		/*
			bottom-top heap gen., 최초 실행시와 우선 순위가 변경되었을 경우 실행됨
			internal node에 대해서만 downheap을 실행하면된다.
		*/
		void adjust_heap(int heap[], int n) {
			int k;
			for (k = n / 2; k >= 1; k--) {
				downheap(heap, k);
			}
		}

		void print_heap(int heap[]) {
			int i;
			printf("\n");
			for (i = 1; i <= nheap; i++) {
				printf("[%c %d %c]", int2name(heap[i]), check[heap[i]], int2name(parent[heap[i]]));
			}
		}

		int pq_update(int heap[], int v, int accu_wt) {
			if (check[v] == UNSEEN) {
				heap[++nheap] = v; // 정점 v가 아직 보이지 않는 정점이라면, heap에 정점 v를 추가한다.
				check[v] = accu_wt;      // p는 정점 v의 가중치에 해당한다.(음수 값으로 들어온다)
				upheap(heap, nheap); // heap을 재조정한다.
				return 1;
			}
			else {
				if (check[v] < accu_wt) {
					// 새로 들어온 가중치가 더 높다면 
					check[v] = accu_wt;
					adjust_heap(heap, nheap);
					return 1;
				}
				else {
					return 0;
				}
			}
		}

		/*
			shortest path problem에서
			시작 노드에서 각 노드로 가능 최단 경로의 길이 뿐만 아니라,
			경로를 저장하기 위해 pq_update를 수정한 함수
			G_spp, 노드 포인터 배열을 계속 업데이트 해준다.
		*/

		int pq_update_spp(int h[], node* G_spp[], int v, int accu_wt, int par) {

			if (check[v] == UNSEEN) {
				heap[++nheap] = v; // 정점 v가 아직 보이지 않는 정점이라면, heap에 정점 v를 추가한다.
				check[v] = accu_wt;      // p는 정점 v의 가중치에 해당한다.(음수 값으로 들어온다)
				upheap(heap, nheap); // heap을 재조정한다.

				node* newnode = (node*) malloc(sizeof(node)); 
				newnode->vertex = v;
				newnode->weight = 0;
				newnode->next = G_spp[par];
				G_spp[v] = newnode;
				return 1;
			}
			else {
				if (check[v] < accu_wt) {
					// 새로 들어온 가중치가 더 높다면 
					check[v] = accu_wt;
					adjust_heap(heap, nheap);
					G_spp[v]->next = G_spp[par];
					return 1;
				}
				else {
					return 0;
				}
			}
		}

		void pq_init() {
			nheap = 0;
		}

		int pq_empty() {
			if (nheap == 0) return 1;
			return 0;
		}

		int pq_extract(int heap[]) {
			int v = heap[1];
			heap[1] = heap[nheap--];
			downheap(heap, 1);
			return v;
		}

		int name2int(char c) {
			return Graph::name2int(c);
		}

		int int2name(int i) {
			return Graph::int2name(i);
		}

		/*
			dijkstra 알고리즘을 위한 인접행렬을 채우는 함수
		*/
		void input_adjmatrix(int G[][MAX_VERTEX], int* v, int* e) {
			char vertex[3];
			int i, j, k, w;

			printf("\nInput number of Vertex & Edge\n");
			fscanf(fp, "%d %d", v, e);
/*
			for (i = 0; i < *v; i++)
				for (j = 0; j < *v; j++)
					G[i][j] = 0;
*/
			for (i = 0; i < *v; i++) {
				for (j = 0; j < *v; j++) {
					G[i][j] = INFINITE;
				}
			}

			for (i = 0; i < *v; i++)
				G[i][i] = 0;

			for (k = 0; k < *e; k++) {
				if (fp == stdin)
					printf("\nInput two Vertex consist of Edge & its Weight --> ");
				fscanf(fp, "%s %d", vertex, &w);
				i = name2int(vertex[0]);
				j = name2int(vertex[1]);
				G[i][j] = w;
				G[j][i] = w;
			}
		}
		
		void input_adjlist(node* G[], int* V, int* E) {
			char vertex[3];
			int i, j, w;
			node* t;
			printf("\nInput number of Vetex & Edge\n");
			fscanf(fp, "%d %d", V, E);
			for (i = 0; i < *V; i++)
				G[i] = NULL;
			for (j = 0; j < *E; j++) {
				printf("\nInput two Vertex consist of Edge & its Weight --> ");
				fscanf(fp, "%s %d", vertex, &w);

				i = name2int(vertex[0]);
				t = (node*)malloc(sizeof(node));
				t->vertex = name2int(vertex[1]);
				t->weight = w;
				t->next = G[i];
				G[i] = t;
				// 무향 그래프이므로 대칭

				i = name2int(vertex[1]);
				t = (node*)malloc(sizeof(node));
				t->vertex = name2int(vertex[0]);
				t->weight = w;
				t->next = G[i];
				G[i] = t;
			}

		}

		void print_adjlist(node* G[], int V) {
			int i;
			node* t;
			for (i = 0; i < V; i++) {
				printf("\n%c : ", int2name(i));
				for (t = G[i]; t != NULL; t = t->next) {
					printf("[%c %d]", int2name(t->vertex), t->weight);
				}

			}
		}

		void print_tree(int tree[], int n) {
			int i;
			printf("son    ");
			for (i = 0; i < n; i++) {
				printf("%c ", int2name(i));
			}
			printf("\n----------------------------\n");
			printf("parent ");
			for (i = 0; i < n; i++) {
				if (i == 0)printf("  ");
				else {
					printf("%c ", int2name(tree[i]));
				}
			}
		}

		void print_cost(int check[], int n) {
			int i = 0;
			int cost = 0;
			for (i = 1; i < n; i++) {
				cost += check[i];
			}
			printf("%d", cost);
		}

		void visit(int index) {
			printf(" --> %c", int2name(index));
		}

		void PFS_adjlist(node* G[], int V) {
			int i;
			node* t;
			pq_init();

			for (i = 0; i < V; i++) {
				check[i] = UNSEEN;
				//parent[i] = 0; // meaningless?
			}

			for (i = 0; i < V; i++) {
				if (check[i] == UNSEEN) {
					parent[i] = -1;
					pq_update(heap, i, UNSEEN);

					while (!pq_empty()) {

						i = pq_extract(heap);
						check[i] = -check[i]; // 주변 정점을 나무정점으로 

						for (t = G[i]; t != NULL; t = t->next) {
							if (check[t->vertex] < 0) {
								if (pq_update(heap, t->vertex, -t->weight)) {
									parent[t->vertex] = i;
								}
							}
						}
						print_heap(heap);
						visit(i);
					}
				}
			}
		}

		/*
			Graph 위의 start 노드에서 각 노드까지의 최단거리를 check[]에 담아주는 함수
			말 그대로 최단거리만 확인할 수 있다.
			최단거리 뿐만 아니라 해당 최단거리에 해당하는 경로까지 저장하도록 업그레이드 해봅시다.
			node 포인터 배열을 애초에 인수로 넣어두도록 합시다.
		*/
		void shortest_adjlist(node* G[], node *G_spp[], int start, int V) {
			int i;
			node* t;
			pq_init();
			for (i = 0; i < V; i++) {
				check[i] = UNSEEN;
				parent[i] = 0;
			}
			i = start;

			if (check[i] == UNSEEN) {
				parent[i] = -1;
				pq_update_spp(heap, G_spp, i, 0, i);
				while (!pq_empty()) {
				
					i = pq_extract(heap);  // i의 용도는 heap에서 extract된 애를 받아주는 역할 
					check[i] = -check[i];

					for (t = G[i]; t!= NULL; t = t->next) {
						if (check[t->vertex] < 0) { // meaningless?
							if (pq_update_spp(heap, G_spp, t->vertex, -t->weight - check[i], i )) {
								parent[t->vertex] = i;
							}
						}
					}
				} // end of while
			} // end of if
			print_adjlist(G_spp, V);
		} // end of function

		void shortest_dijkstra(int G[][MAX_VERTEX], node* G_spp[], int start, int V) {

			int x = 0, y, d;
			int i, checked = 0;
			for (x = 0; x < V; x++) {
				// 시작 정점 start로 distance[]와 parent[]를 초기화 한다.
				distance_dijkstra[x] = G[start][x];
				if (x != start) parent[x] = start;
			}

		
			check[start] = 1; // 시작 정점 start를 체크함
			checked++;

			for (int j = 0; j < V; j++) {
				G_spp[j] = (node*)malloc(sizeof(node));
				G_spp[j]->vertex = j;
				G_spp[j]->weight = 0;
				G_spp[j]->next = NULL;
			}

			for (int j = 0; j < V; j++) {
				if(j != start)
					G_spp[j]->next = G_spp[start];
			}
		

			while (checked < V) {
				x = 0;

				while (check[x]) x++;

				for (i = x; i < V; i++) {
					if (check[i] == 0 && distance_dijkstra[i] < distance_dijkstra[x]) x = i;
				}

				// x는 체크되지 않은 정점 중에서 start로부터의 가중치가 가장 작은 정점
				check[x] = 1;
				checked++;

				for (y = 0; y < V; y++) {
					if (x == y || G[x][y] >= INFINITE || check[y]) continue;
					d = distance_dijkstra[x] + G[x][y];
					if (d < distance_dijkstra[y]) {
						distance_dijkstra[y] = d;
						parent[y] = x;
						G_spp[y]->next = G_spp[x];
					}
				}
			}
			print_adjlist(G_spp, V);
		}

		void Main(int argc, char* argv[]) {
			int V, E;
			if (argc < 2)
				fp = stdin;
			else {
				if ((fp = fopen(argv[1], "rt")) == NULL) {
					printf("\n That file does not exist !");
					exit(1);
				}
			}

			int mode = 1;

			if (mode == 1) {
				input_adjlist(G_list, &V, &E);
				printf("\n\nOrigianl Graph\n");
				print_adjlist(G_list, V);
				printf("\n\nVisit order of Minimum Spanning Tree\n");
				PFS_adjlist(G_list, V);
				printf("\n\nTree structure\n");
				print_tree(parent, V);
				printf("\n\nMinimum Cost is \n");
				print_cost(check, V);
				printf("\n\nShortest path from F is \n");
				shortest_adjlist(G_list, G_spp, 5, V);
			}
			else {
				input_adjmatrix(G_matrix, &V, &E);
				printf("\n\nDijkstra path from F is \n");
				shortest_dijkstra(G_matrix, G_spp, 5, V);
			}

			fclose(fp);
		}
	}
	
	namespace Kruskal {


		FILE *fp;
		int parent[MAX_VERTEX];
		int height[MAX_VERTEX];
		int cost;

		edge Edge[MAX_ELEMENT];

		int heap[MAX_ELEMENT];
		int nheap = 0;


		int name2int(char c) {
			return Graph::name2int(c);
		}

		char int2name(int i) {
			return Graph::int2name(i);
		}

		void upheap(int heap[], int k) {
			int v;
			v = heap[k];
			while (Edge[heap[k / 2]].weight >= Edge[heap[v]].weight && k / 2 > 0) {
				heap[k] = heap[k / 2];
				k /= 2;
			}
			heap[k] = v;
		}


		void downheap(int heap[], int k) {
			int i, v;
			v = heap[k];
			while (k <= nheap / 2) {
				i = k << 1;
				if (i < nheap && Edge[heap[i]].weight > Edge[heap[i + 1]].weight) i++;
				if (Edge[v].weight <= Edge[heap[i]].weight) break;
				heap[k] = heap[i];
				k = i;
			}
			heap[k] = v;
		}
		void print_heap(int heap[], int n) {
			int i;
			printf("\n");
			for (i = 1; i <= n; i++) {
				printf("%c%c %d ", int2name(Edge[heap[i]].v1), int2name(Edge[heap[i]].v2), Edge[heap[i]].weight);
			}
			printf("\n");
		}
		void pq_insert(int heap[], int v) {
			heap[++nheap] = v;
			upheap(heap, nheap);
		}
		
		void pq_init() {
			nheap = 0;
		}

		int pq_empty() {
			if (nheap == 0)	return 1;
			return 0;
		}

		int pq_extract(int heap[]) {
			int v = heap[1];
			heap[1] = heap[nheap--];
			downheap(heap, 1);
			return v;
		}

		void union_set2(int elem, int asso) {
			if (height[elem] == height[asso]) {
				height[asso]++;
				parent[elem] = asso;
				return;
			}
	
			if (height[elem] > height[asso])
				parent[asso] = elem;
			else {
				parent[elem] = asso;
			}
			return;
		}

		int find_set2(int elem, int asso, int flag) {
			int i = elem, j = asso;
			while (parent[i] >= 0)	i = parent[i];
			while (parent[j] >= 0)	j = parent[j];
			if (flag == UNION && i != j) union_set2(i, j);
			return i == j;
		}

		/*
			return 1 when same set -> the link in interest will make closed loop
			return 0 when different set -> the link in interest will not make closed loop.
				so this link can be added to the set
		*/
		int  is_closing(int elem, int asso, int flag) {
			return find_set2(elem, asso, flag);
		}

		/*
			parent initialization
		*/
		void find_init(int elem) {
			int i;
			for (i = 0; i < elem; i++)
				parent[i] = -1;
		}
		void input_edge(edge e[], int* V, int* E) {
			char vertex[3];
			int j, w;
			printf("\nInput number of Vertex & Edge\n");
			fscanf(fp, "%d %d", V, E);
			for (j = 0; j < *E; j++) {
				printf("\nInput two Vertex consist of Edge and its weight --> ");
				fscanf(fp, "%s %d", vertex, &w);
				vertex[2] = NULL;
				e[j].v1 = name2int(vertex[0]);
				e[j].v2 = name2int(vertex[1]);
				e[j].weight = w;
			}
		}

		void visit(int e) {
			printf("%c %c  ", int2name(Edge[e].v1), int2name(Edge[e].v2));
			cost += Edge[e].weight;
		}

		void kruskal(edge e[], int V, int E) {
			int n, trial = 0;
			find_init(V);
			pq_init();

			for (n = 0; n < E; n++)
				pq_insert(heap, n);

			print_heap(heap, nheap);
			n = 0;
			while (!pq_empty()) {
				trial = pq_extract(heap);
				if (!is_closing(e[trial].v1, e[trial].v2, UNION)) {
					visit(trial);
					n++;
				}
				if (n == V - 1) break;	
			}
		}


		void Main(int argc, char* argv[]) {
			int V, E;
			if (argc < 2) fp = stdin;
			else {
				if ((fp = fopen(argv[1], "rt")) == NULL) {
					printf("\n That file does not exist !");
					exit(1);
				}
			}

			input_edge(Edge, &V, &E);
			printf("\n\nVisited Edge of Minimum Spanning Tree\n");
			kruskal(Edge, V, E);
			printf("\n\nMinimum Cost is : %d", cost);
			fclose(fp);
		}
	}

} // end of namespace WeightGraph

namespace DirGraph {

	FILE* fp;
	int  G_matrix[MAX_VERTEX][MAX_VERTEX];
	int  G_matrix_floyd[MAX_VERTEX][MAX_VERTEX];
	node* G[MAX_VERTEX];
	head  net[MAX_VERTEX];

	int check[MAX_VERTEX];
	int order = 0; // strong test에서 사용되는 변수
	DQS stack_strong(MAX_VERTEX);
	int stack_init_flag = 0;
	

	/*
	list 출력 함수
	*/
	void print_adjlist(node* G[], int* V) {
		int size = *V;
		int i = 0, j = 0, k = 0;

		node* temp = NULL;
		int* condition = NULL;
		condition = (int*)malloc(sizeof(int) * size);

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


	void input_adjmatrix(int G_mat[][MAX_VERTEX], int* V, int* E) {
		char vertex[3];
		int i, j, k;
		printf("\nInput number of Vertex & Edge\n");
		fscanf(fp, "%d %d", V, E);
		for (i = 0; i < *V; i++) {
			for (j = 0; j < *V; j++) {
				G_mat[i][j] = 0;
			}
		}
		for (i = 0; i < *V; i++)	G_mat[i][i] = 0;

		for (k = 0; k < *E; k++) {
			printf("\n Input two Vertex consist of Edge ->");
			fscanf(fp, "%s", vertex);
			i = name2int(vertex[0]);
			j = name2int(vertex[1]);
			G_mat[i][j] = 1;
		}

	}
	
	/*
		prepare the adjacent matrix fo floyd algorithm
	*/
	void input_adjmatrix_floyd(int G_mat[][MAX_VERTEX], int* V, int* E) {
		char vertex[3];
		int i, j, k;
		int w;
		printf("\nInput number of Vertex & Edge\n");
		fscanf(fp, "%d %d", V, E);


		for (i = 0; i < *V; i++)
			for (j = 0; j < *V; j++)
				G_mat[i][j] = INFINITE;

		for (i = 0; i < *V; i++)	G_mat[i][i] = 0;
		

		for (k = 0; k < *E; k++) {
			printf("\n Input two Vertex consist of Edge and weight ->");
			fscanf(fp, "%s %d", vertex, &w);
			i = name2int(vertex[0]);
			j = name2int(vertex[1]);
			G_mat[i][j] = w;
		}
	}
	

	void input_adjlist(node* G[], int* V, int* E) {
		char vertex[3];
		int i, j;
		node* t;
		printf("\nInput number of Vertex & Edge\n");
		fscanf(fp, "%d %d", V, E);
		for (i = 0; i < *V; i++) G[i] = NULL; // 이 부분이 다르구나?
		for (j = 0; j < *E; j++) {

			printf("\nInput two Vertex consist of Edge -> ");
			fscanf(fp, "%s", vertex);

			i = name2int(vertex[0]);
			t = (node*)malloc(sizeof(node));
			t->vertex = name2int(vertex[1]);
			t->next = G[i];
			G[i] = t;
		}
	}

	int name2int(char c) {
		return Graph::name2int(c);
	}

	int int2name(int i) {
		return Graph::int2name(i);
	}

	void visit(int index) {
		printf("%c ", int2name(index));
	}

	void DFS_directed(node* G[], int V) {
		int i, j;
		node* t;
		DQS stack(MAX_VERTEX);
		stack.init_stack();
		for (i = 0; i < V; i++) { 
			for (j = 0; j < V; j++) {
				check[j] = 0;  // 이 부분이 차이점
				// nrDFS_adjlist와 비교해보자.
				// 모든 i 정점(출발)에 대해서 도달할 수 있는 곳을
				// 확인하기 전에 check배열을 초기화한다.
			}
			stack.push(i);
			check[i] = 1;
			printf("\n %c : ", int2name(i));
			while (stack.getSize()) {
				j = stack.pop();
				visit(j);
				for (t = G[j]; t != NULL; t = t->next) {
					if (check[t->vertex] == 0) {
						stack.push(t->vertex);
						check[t->vertex] = 1;
					}
				}
			}		
		}	
	} // end of DFS_directed


	/*
		warshall
	*/
	void warshall(int G_mat[][MAX_VERTEX], int V) {
		int x, y, i;

		for (int j = 0; j < V; j++) G_mat[j][j] = 1; 
		// 위 for문은 G_mat의 용도 변경이라고 할 수 있다.

		for (y = 0; y < V; y++)
			for (x = 0; x < V; x++)
				if (G_mat[x][y])
					for (i = 0; i < V; i++)
						if (G_mat[y][i])
							G_mat[x][i] = 1;

		for (y = 0; y < V; y++) {
			printf("%c : ", int2name(y));
			for (x = 0; x < V; x++) {
				if (G_mat[y][x]) {
					printf("%c ", int2name(x));
				}
			}
			printf("\n");
		}
		// 이렇게 해서 얻어지는 G, 2차원배열은 
		// 그 의미가 본래의 의미와 달라진다.
		// 본래의 G는 인접된 정점들에 바로(one bridge) 접근 가능한지의 여부를 저장하는 것
		// 반면 이 함수를 통해 얻어지는 G는 
		// 각 정점에서 다른 정점까지 어떻게든 갈 수 있는지 없는 지의 여부를 저장하는 것
	}

	/*
		floyd
	*/
	void floyd(int G_mat_floyd[][MAX_VERTEX], int V) {
		int x, y, i;
		for (y = 0; y < V; y++)
			for (x = 0; x < V; x++)
				for (i = 0; i < V; i++)
					if (G_mat_floyd[x][y] + G_matrix_floyd[y][i] < G_matrix_floyd[x][i])
						G_mat_floyd[x][i] = G_mat_floyd[x][y] + G_mat_floyd[y][i];

		for (y = 0; y < V; y++) {
			printf("%c : ", int2name(y));
			for (x = 0; x < V; x++) {
				if (G_mat_floyd[y][x] < INFINITE)
					printf("%2d ", G_mat_floyd[y][x]);
				else {
					printf("%2c ", 'X');
				}
			}
			printf("\n");
		}
	}

	
	/*
		Topological sorting에서 필요한 각 정점의 indegree를 저장하는 함수
	*/
	void set_count_indegree(head net[], int V) {
		int i, j;
		int count;
		node* t;
		for (i = 0; i < V; i++) {
			count = 0;
			for (j = 0; j < V; j++) {
				for (t = net[j].next; t; t = t->next) {
					if (t->vertex == i)count++;
				}
			}
			net[i].count = count;
		}
	}

	void topsort(head net[], int V) {
		int i, j, k;
		node* ptr;
		DQS stack(MAX_VERTEX);

		stack.init_stack();

		set_count_indegree(net, V);

		for (i = 0; i < V; i++) {
			if (net[i].count == 0) {
				void set_count_outdegree(head net[], int V);
				void revtopsort(head net[], int V);

				stack.push(i);
			}
		}

		for (i = 0; i < V; i++) {
			if (stack.getSize() == 0) {
				printf("\nNetwork has a cycle, Sort Terminated !");
				return;
			}
			else {
				j = stack.pop();
				//printf("%c is poped from this stack\n", int2name(j));
				printf("[%c visited]\n", int2name(j));
				for (ptr = net[j].next; ptr != NULL; ptr = ptr->next) {
					k = ptr->vertex;
					net[k].count--;
					if (net[k].count == 0) {
						stack.push(k);
						//printf("%c is pushed into this stack\n", int2name(k));
					}
				}
			}
		}
		printf("\n\nend of topological sorting\n");
	}

	void set_count_outdegree(head net[], int V) {
		int i;
		int count;
		node* t;
		for (i = 0; i < V; i++) {
			count = 0;
			for (t = net[i].next; t; t = t->next)
				count++;
			net[i].count = count;
		}
	}

	void revtopsort(head net[], int V) {
		int i, j, k;
		node* ptr;
		DQS stack(MAX_VERTEX);
		stack.init_stack();

		set_count_outdegree(net, V);

		for (i = 0; i < V; i++) {
			if (net[i].count == 0) stack.push(i);
			printf("%c %d\n", int2name(i), net[i].count);
		}

		for (i = 0; i < V; i++) {
			if (stack.getSize() == 0) {
				printf("\nNetwork has a cycle. reovtopsort terminated !");
				return;
			}
			else {
				j = stack.pop();
				printf("[%c visited]\n", int2name(j));
				for (k = 0; k < V; k++) {
					for (ptr = net[k].next; ptr; ptr = ptr->next) {
						if (ptr->vertex == j) {
							net[k].count--;
							if (net[k].count == 0)
								stack.push(k);
						}
					}
				}
			}
		}
		printf("\n\nend of Reverse topological sorting\n");
	}
	
	int strong_recur(node* G[], int i) {
		int m, min;
		int k;
		int flag;
		node* t;
		check[i] = min = ++order;
		// stack을 처음에 한 번 초기화 시켜주는 역할
		if (!stack_init_flag) {
			stack_strong.init_stack();
			stack_init_flag = 1;
		}
		stack_strong.push(i);
		for (t = G[i]; t != NULL; t = t->next) {
			if (check[t->vertex] == 0)
				m = strong_recur(G, t->vertex);
			else
				m = check[t->vertex];

			if (m < min) min = m;
		}
		if (min == check[i]) {
			flag = 0;
			while ((k = stack_strong.pop()) != i) {
				printf("[%c]-", int2name(k));
				check[k] = MAX_VERTEX + 1;
				flag = 1;
			}
			if (flag) printf("[%c]\n", int2name(k));
		}
		return min;
	}
	
	void strong(node* G[], int V) {
		int i;
		for (i = 0; i < V; i++)
			check[i] = 0;
		for (i = 0; i < V; i++) {
			if (check[i] == 0)
				strong_recur(G, i);
		}
	}

	void Main(int argc, char* argv[]) {

		int V, E;

		enum mymode { DFS_dir, Warshall, Floyd, Topological, Strong};
		mymode mode = Strong;

		argc = 2;
		argv[0] = (char*)"algorithm.exe";
		switch (mode) {
			case 0:
			case 1: argv[1] = (char*) "../Debug/res/dgraph.txt";   break;
			case 3: argv[1] = (char*) "../Debug/res/topology.txt"; break;
			case 2:	argv[1] = (char*) "../Debug/res/floyd.txt";    break;
			case 4: argv[1] = (char*) "../Debug/res/strong.txt";   break;
				                     
			default:break;
		}
	
	
		if (argc < 2)
			fp = stdin;
		else {
			if ((fp = fopen(argv[1], "rt")) == NULL) {
				printf("\n That file does not exist !");
				exit(1);
			}
		}

		switch (mode) {
			case 0:
				input_adjlist(G, &V, &E);
				printf("\n\nDFS_directed\n");
				DFS_directed(G, V);
				break;
			case 1:
				input_adjmatrix(G_matrix, &V, &E);
				printf("\n\nWarshall\n");
				warshall(G_matrix, V);
				break;
			case 2:
				input_adjmatrix_floyd(G_matrix_floyd, &V, &E);
				printf("\n\nFloyd\n");
				floyd(G_matrix_floyd, V);
				break;
			case 3:
				input_adjlist(G, &V, &E);
				for (int i = 0; i < V; i++) {
					net[i].next = G[i];
				}


				printf("\n\nTopological sorting\n");
				topsort(net, V);

				printf("\n\nReverse Topological sorting\n");
				revtopsort(net, V);
				break;

			case 4:
				input_adjlist(G, &V, &E);
				printf("\n\nStrong connection test\n");
				strong(G, V);
				break;

			default: break;
		}

		fclose(fp);
	}


}

namespace Network {

	FILE* fp;
	int  G_matrix[MAX_VERTEX][MAX_VERTEX];
	node* G[MAX_VERTEX];
	head  net[MAX_VERTEX];

	int earliest[MAX_VERTEX];
	int latest  [MAX_VERTEX];

	int Capacity[MAX_VERTEX][MAX_VERTEX];
	int Flow	[MAX_VERTEX][MAX_VERTEX];
	int Residual[MAX_VERTEX][MAX_VERTEX];
	int check	[MAX_VERTEX];
	int parent	[MAX_VERTEX];
	int path	[MAX_VERTEX];

	char int2name(int i) {
		return Graph::int2name(i);
	}

	int  name2int(char c) {
		return Graph::name2int(c);
	}

	char int2name_flow(int i) {
		if (i == 0) return SOURCE;
		if (i == 1) return SINK;
		return i + 'A' - 2;
	}

	int	 name2int_flow(char c) {
		if (c == SOURCE) return 0;
		if (c == SINK) return 1;
		return c - 'A' + 2;
	}


	void input_adjlist(node* G[], int* state, int* work) {
		char vertex[3];
		int i, j;
		int time;
		node* t;
		printf("\nInput number of State & Work\n");
		fscanf(fp, "%d %d", state, work);
		for (i = 0; i < *state; i++) G[i] = NULL; 
		for (j = 0; j < *work; j++) {

			printf("\nInput two State consist of Work and Time -> ");
			fscanf(fp, "%s %d", vertex, &time);


			i = name2int(vertex[0]);
			t = (node*)malloc(sizeof(node));
			t->vertex = name2int(vertex[1]);
			t->next = G[i];
			t->weight = time;
			t->act = (char*)malloc(sizeof(char) * 3);
			memcpy(t->act, vertex, 3);
			G[i] = t;
		}
	}

	void input_adjmatrix_flow(int G[][MAX_VERTEX], int* V, int* E) {
		char vertex[3];
		int i, j, k, w;

		printf("\nInput number of Vertex & Edge\n");
		fscanf(fp, "%d %d", V, E);
	
		for (i = 0; i < *V; i++) {
			for (j = 0; j < *V; j++) {
				G[i][j] = 0;
			}
		}

		//for (i = 0; i < *V; i++)
		//	G[i][i] = 0;

		for (k = 0; k < *E; k++) {
			if (fp == stdin)
				printf("\nInput two Vertex consist of Edge & its Weight --> ");
			fscanf(fp, "%s %d", vertex, &w);
			i = name2int_flow(vertex[0]);
			j = name2int_flow(vertex[1]);
			G[i][j] = w;
		}

	}
	
	void set_count_indegree(head net[], int V) {
		int i, j;
		int count;
		node* t;
		for (i = 0; i < V; i++) {
			count = 0;
			for (j = 0; j < V; j++) {
				for (t = net[j].next; t; t = t->next) {
					if (t->vertex == i) count++;
				}
			}
			net[i].count = count;
		}
	}

	void set_count_outdegree(head net[], int V) {
		int i;
		int count;
		node* t;
		for (i = 0; i < V; i++) {
			count = 0;
			for (t = net[i].next; t; t = t->next)
				count++;
			net[i].count = count;
		}

	}

	void forword_stage(head net[], int V) {
		int i, j, k;
		node* ptr;
		DQS stack(MAX_VERTEX);
		stack.init_stack();
		set_count_indegree(net, V);

		for (i = 0; i < V; i++) earliest[i] = 0;
		for (i = 0; i < V; i++) {
			if (!net[i].count) {
				stack.push(i);
			}
		}

		for (i = 0; i < V; i++) {
			if (stack.getSize() == 0) {
				// 위상 정렬에서 스택이 early-empty되는 경우 : 회로를 포함하고 있는 경우
				printf("\nNetwork has a cycle. Sort Terminated !");
				return;
			}
			else {
				j = stack.pop();
				for (ptr = net[j].next; ptr; ptr = ptr->next) {
					k = ptr->vertex;
					net[k].count--;
					if (net[k].count == 0) {
						stack.push(k);
					}
					if (earliest[k] < earliest[j] + ptr->weight) {
						earliest[k] = earliest[j] + ptr->weight;
						// earlist(y) = 정점 y를 직접 가리키는 정점 x에 대해
						// (earlist(x) + <x,y>)의 가중치의 최대값
					}
				}
			}
		}	

	}

	void backword_stage(head net[], int V) {

		int i, j, k, l = 0;
		node* ptr;
		DQS stack(MAX_VERTEX);
		stack.init_stack();
		set_count_outdegree(net, V);
		
		for (i = 0; i < V; i++) {
			latest[i] = earliest[V - 1];
			// critical path의 length에 해당하는 것으로 초기화 시켜준다.
		}

		for (i = 0; i < V; i++) {
			if (net[i].count == 0) {
				stack.push(i);
			}
		}

		for (i = 0; i < V; i++) {
			if (stack.getSize() == 0) {
				printf("\nNetwork has a cycle. Sort Terminated !");
				return;
			}
			else {
				j = stack.pop();
				for (l = 0; l < V; l++) {
					for (ptr = net[l].next; ptr; ptr = ptr->next) {
						if (ptr->vertex == j) {
							k = l;
							net[k].count--;
							if (net[k].count == 0) {
								stack.push(k);
							}
							if (latest[k] > latest[j] - ptr->weight) {
								latest[k] = latest[j] - ptr->weight;
							}
						}
					}
				}
			}
		}



	}

	void print_critical_activity(head net[], int V) {
		int i;
		int e, l;
		node* t;
		printf("\n\nCritical Activities");
		printf("\nEdge	Action	Early	Late	Late-Early	Critical?"
			"\n----	------	-----	----	----------	---------");

		for (i = 0; i < V; i++) {
			for (t = net[i].next; t; t = t->next) {
				e = earliest[i];
				l = latest[i] - t->weight;
				printf("\n<%c,%c>	%-7s %-5d	%-5d	%-10d	%s",
					int2name(i), int2name(t->vertex), t->act, e, l, l - e,
					(l - e == 0) ? "Yes" : "No");
			}
		}
	}


	/*
		maximum	flow test
	*/


	void clear_matrix(int mat[][MAX_VERTEX], int V) {
		int i, j;
		for (i = 0; i < V; i++)
			for (j = 0; j < V; j++)
				mat[i][j] = 0;
	}

	int get_augment_path(int Residual[][MAX_VERTEX], int V, char S, char T) {
		int i, j;
		Queue queue(MAX_VERTEX);
		queue.init_queue();
		for (i = 0; i < V; i++) {
			check[i] = 0;
			parent[i] = -1;
		}
		i = name2int_flow(S);
		if (check[i] == 0) {
			queue.put(i);
			check[i] = 1;
			while (queue.getSize() != 0) {
				i = queue.get();
				if (i == name2int_flow(T)) {
					break; // 출구를 찾으면 종료 
				}
				for (j = 0; j < V; j++) {
					if (Residual[i][j] != 0) {
						if (check[j] == 0) {
							queue.put(j);
							check[j] = 1;
							parent[j] = i; // 나무 구조 생성 
						}
					}
				}
			}
		}

		set_path();
		if (i == name2int_flow(SINK)) return 1;
		else return 0;
	}

	void set_path(void) {
		int* temp;
		int i, count = 0;
		temp = (int*)malloc(sizeof(int) * MAX_VERTEX);
		i = name2int_flow(SINK);
		printf("\n");
		while (i >= 0) {
			// 확대 경로의 역순을 temp[] 배열에 저장
			temp[count] = i;
			i = parent[i];
			count++;
		}
		for (i = 0; i < count; i++)
			path[i] = temp[count - i - 1];

		path[i] = -1;
		free(temp);


	}

	void construct_residual(int c[][MAX_VERTEX], int f[][MAX_VERTEX], int r[][MAX_VERTEX], int V) {
		int i, j;
		for (i = 0; i < V; i++)
			for (j = 0; j < V; j++)
				r[i][j] = c[i][j] - f[i][j];
	}

	void network_flow(int c[][MAX_VERTEX], int f[][MAX_VERTEX], int r[][MAX_VERTEX], int V, char S, char T) {
		int i, min;
		clear_matrix(f, V);
		clear_matrix(r, V);
		construct_residual(c, f, r, V);
		while (get_augment_path(r, V, S, T)) {
			min = INT_MAX;
			for (i = 1; path[i] >= 0; i++) {
				if (min > r[path[i - 1]][path[i]]) min = r[path[i - 1]][path[i]];
			}
			for (i = 1; path[i] >= 0; i++) {
				f[path[i - 1]][path[i]] = f[path[i - 1]][path[i]] + min;
				f[path[i]][path[i - 1]] = -f[path[i]][path[i - 1]];
			}
			construct_residual(c, f, r, V);
			print_flow();
		}
		


	}

	void print_flow() {
		printf("parent : ");
		for (int i = 0; i < 6; i++) {
			printf("%d ", parent[i]);
		}
		printf("\n");

		printf("path : ");
		for (int i = 0; i < 6; i++) {
			printf("%d ", path[i]);
		}
		printf("\n");

		printf("max flow\n");
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				printf("%4d ", Flow[i][j]);
			}
			printf("\n");
		}
	}


	void Main(int argc, char* argv[]) {

		int V, E;

		enum mymode {Critical, FLOW};
		mymode mode = FLOW;
	
		argc = 2;
		argv[0] = (char*)"algorithm.exe";
		switch (mode) {

			case 0: argv[1] = (char*) "../Debug/res/critical.txt";   break;
			case 1: argv[1] = (char*) "../Debug/res/flow.txt"; break;

			default:break;
		}


		if (argc < 2)
			fp = stdin;
		else {
			if ((fp = fopen(argv[1], "rt")) == NULL) {
				printf("\n That file does not exist !");
				exit(1);
			}
		}

		switch (mode) {
		case 0:

			input_adjlist(G, &V, &E);
			printf("\n\nCritical Activity\n");
			for (int i = 0; i < V; i++) {
				net[i].next = G[i];
			}
			forword_stage(net, V);
			backword_stage(net, V);
			print_critical_activity(net, V);
			break;

		case 1:
			input_adjmatrix_flow(Capacity, &V, &E);
			printf("\n\nMax flow test\n");
			network_flow(Capacity, Flow, Residual, V, SOURCE, SINK);
			break;

		default: break;
		}

		fclose(fp);
	}
	
}