#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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

		int roopCount = 0;
		for(t = G[i]; t->next != NULL; t = t->next){
			roopCount++;
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
		if (roopCount == 0) isArti[i] = 1;
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
		node* G_list[MAX_VERTEX];
		int check[MAX_VERTEX];
		int parent[MAX_VERTEX];
		int nheap = 0;
		int heap[MAX_VERTEX];

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

		int pq_update(int heap[], int v, int p) {
			if (check[v] == UNSEEN) {
				heap[++nheap] = v; // 정점 v가 아직 보이지 않는 정점이라면, heap에 정점 v를 추가한다.
				check[v] = p;      // p는 정점 v의 가중치에 해당한다.(음수 값으로 들어온다)
				upheap(heap, nheap); // heap을 재조정한다.
				return 1;
			}
			else {
				if (check[v] < p) {
					// 새로 들어온 가중치가 더 높다면 
					check[v] = p;
					adjust_heap(heap, nheap);
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

			input_adjlist(G_list, &V, &E);
			printf("\n\nOrigianl Graph\n");
			print_adjlist(G_list, V);
			printf("\n\nVisit order of Minimum Spanning Tree\n");
			PFS_adjlist(G_list, V);
			printf("\n\nTree structure\n");
			print_tree(parent, V);
			printf("\n\nMinimum Cost is \n");
			print_cost(check, V);
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


