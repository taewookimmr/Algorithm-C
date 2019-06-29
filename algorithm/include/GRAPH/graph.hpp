#pragma once

#include <stdio.h>
#include "../GlobalVariables/GV_Graph.hpp"

namespace Graph {

	typedef struct _node {
		struct _node *next;
		int vertex;
	} node;

	void input_adjmatrix(int(*arr)[MAX_VERTEX], int* v, int* e);
	void input_adjlist(node* arr[], int* v, int* e);
	void print_adjmatrix(int (*G)[MAX_VERTEX], int *V);
	void print_adjlist(node *G[], int *V);
	int  name2int(char c);
	char int2name(int i);


	void DFS_recur(int(*G)[MAX_VERTEX], int V, int i);
	void DFS_adjmatrix(int(*G)[MAX_VERTEX], int V);
	void nrDFS_ajdmatrix(int(*G)[MAX_VERTEX], int V);

	void DFS_recur_list(node* G[], int V, int i);
	void DFS_adjlist(node* G[], int V);
	void nrDFS_adjlist(node* G[], int V);

	void BFS_adjmatrix(int(*G)[MAX_VERTEX], int V);
	void BFS_adjlist(node* G[], int V);
	int  num_compo_adjmatix(int(*G)[MAX_VERTEX], int V);

	int AP_recur(node* G[], int i);
	void AP_search(node* G[], int V);


	void Main_graph(int argc, char *argv[]);
	void Main_graph_list(int argc, char* argv[]);

}

namespace WeightGraph {

	namespace PFS {
		typedef struct _node {
			struct _node* next;
			int vertex;
			int weight;
		} node;


		void upheap(int heap[], int k);
		void downheap(int heap[], int l);
		void adjust_heap(int heap[], int n);
		void print_heap(int heap[]);

		int pq_update(int h[], int v, int p);
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

		void PFS_adjlist(node* G[], int V);

		void Main(int argc, char* argv[]);
	}

	namespace Kruskal {
		typedef struct _edge {
			int v1, v2;
			int weight;
		}edge;

		int name2int(char c);
		char int2name(int i);
		void upheap(int heap[], int k);
		void downheap(int heap[], int k);
		void print_heap(int heap[], int n);
		void pq_insert(int heap[], int v);
		void pq_init();
		int pq_empty();
		int pq_extract(int h);
		void union_set2(int elem, int asso);
		int  find_set2(int elem, int asso, int flag);
		int  is_closing(int elem, int asso, int flag);
		void find_init(int elem);
		void input_edge(edge e[], int* V, int* E);
		void visit(int e);
		void kruskal(edge e[], int V, int E);
		void Main(int argc, char* argv[]);
	}

}

