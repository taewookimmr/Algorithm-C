#include "wGraph.hpp"

namespace WeightGraph {


	void downheap(int heap[], int l);
	void adjust_heap(int heap[], int n);
	void print_heap(int heap[]);

	int pq_update(int h[], int v, int p) {
		if (check[v] == UNSEEN) {
			h[++nheap] = v; // ���� v�� ���� ������ �ʴ� �����̶��, heap�� ���� v�� �߰��Ѵ�.
			check[v] = p;   // p�� ���� v�� ����ġ�� �ش��Ѵ�.
			upheap(h, nheap); // heap�� �������Ѵ�.
			return 1;
		}
		else {
			if (check[v] < p) {
				// ���� ���� ����ġ�� �� ���ٸ� 
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
					check[i] = -check[i]; // �ֺ� ������ ������������ 
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