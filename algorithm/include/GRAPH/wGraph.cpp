#include "wGraph.hpp"

namespace WeightGraph {


	void downheap(int heap[], int l);
	void adjust_heap(int heap[], int n);
	void print_heap(int heap[]);

	int pq_update(int h[], int v, int p) {
		if (check[v] == UNSEEN) {
			h[++nheap] = v; // 정점 v가 아직 보이지 않는 정점이라면, heap에 정점 v를 추가한다.
			check[v] = p;   // p는 정점 v의 가중치에 해당한다.
			upheap(h, nheap); // heap을 재조정한다.
			return 1;
		}
		else {
			if (check[v] < p) {
				// 새로 들어온 가중치가 더 높다면 
				check[v] = p;
				adjust_heap(h, nheap);
				return 1;
			}
			else {
				return 0;
			}
		}
	}
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



	void PFS_adjlist(node* G[], int V) {
		int i;
		node* t;
		pq_init();

		for (i = 0; i < V; i++) {
			check[i] = UNSEEN;
			parent[i] = 0;
		}

		for (i = 0; i < V; i++) {
			if (check[i] == UNSEEN) {
				parent[i] = -1;
				pq_update(heap, i, UNSEEN);
		
				while (!pq_empty()) {
					print_heap(heap);
					i = pq_extract(heap);
					check[i] = -check[i]; // 주변 정점을 나무정점으로 
					visit(i);
					for (t = G[i]; t != NULL; t = t->next) {
						if (check[t->vertex] < 0) {
							if (pq_update(heap, t->vertex, -t->weight)) {
								parent[t->vertex] = i;
							}
						}
						
					}
				}
			}
		}
	}
} // end of namespace WeightGraph