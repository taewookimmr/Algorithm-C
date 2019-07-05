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

	int	 name2int_flow(char c);
	char int2name_flow(int i);


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

	typedef struct _node {
		struct _node* next;
		int vertex;
		int weight;
	} node;

	typedef struct _edge {
		int v1, v2;
		int weight;
	}edge;


	namespace PFS {


		void upheap(int heap[], int k);
		void downheap(int heap[], int l);
		void adjust_heap(int heap[], int n);
		void print_heap(int heap[]);

		int pq_update(int h[], int v, int accu_wt);
		int pq_update_spp(int h[], node* G_spp, int v, int accu_wt, int par);
		void pq_init();
		int pq_empty();
		int pq_extract(int heap[]);

		int name2int(char c);
		int int2name(int i);

		void input_adjmatrix(int G[][MAX_VERTEX], int* v, int* e);

		void input_adjlist(node* G[], int* V, int* E);
		void print_adjlist(node* G[], int V);

		void print_tree(int tree[], int n);
		void print_cost(int check[], int n);
		void visit(int index);

		void PFS_adjlist(node* G[], int V);
		void shortest_adjlist(node* G[], node* G_spp[], int start, int V);
		void shortest_dijkstra(int G[][MAX_VERTEX], node* G_spp[], int start, int V);

		void Main(int argc, char* argv[]);
	}

	namespace Kruskal {
	

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

namespace DirGraph {
	typedef struct _node {
		struct _node* next;
		int vertex;
	} node;

	typedef struct _head {
		int count;
		node* next;
	} head;


	void print_adjlist(node* G[], int* V);
	void input_adjmatrix(int G_mat[][MAX_VERTEX], int* V, int* E);
	void input_adjmatrix_floyd(int G_mat_floyd[][MAX_VERTEX], int* V, int* E);
	void input_adjlist(node* G[], int* V, int* E);
	int name2int(char c);
	int int2name(int i);

	void visit(int index);
	void DFS_directed(node* G[], int V);
	void warshall(int G_mat[][MAX_VERTEX], int V);
	void floyd   (int G_mat_floyd[][MAX_VERTEX], int V);

	void set_count_indegree(head net[], int V);
	void topsort(head net[], int V);

	void set_count_outdegree(head net[], int V);
	void revtopsort(head net[], int V);

	int strong_recur(node* G[], int i);
	void strong(node* G[], int V);

	void Main(int argc, char* argv[]);
}


namespace Network {

	typedef struct _node {
		struct _node* next;
		int vertex;
		int weight;
		char* act;
	} node;

	typedef struct _head {
		int count;
		node* next;
	} head;

	void input_adjlist(node* G[], int* state, int* act);
	void input_adjmatrix_(int G[][MAX_VERTEX], int* V, int* E);

	char int2name(int i);
	int  name2int(char c);
	void set_count_indegree(head net[], int V);
	void set_count_outdegree(head net[], int V);
	void forword_stage(head net[], int V);
	void backword_stage(head net[], int V);
	void print_critical_activity(head net[], int V);


	void clear_matrix(int mat[][MAX_VERTEX], int V);
	int get_augment_path(int G[][MAX_VERTEX], int V, char S, char T);
	void set_path(void);
	void construct_residual(int c[][MAX_VERTEX], int f[][MAX_VERTEX], int r[][MAX_VERTEX], int V);
	void network_flow(int c[][MAX_VERTEX], int f[][MAX_VERTEX], int r[][MAX_VERTEX], int V, char S, char T);
	
	void print_flow();
	void Main(int argc, char* argv[]);

}