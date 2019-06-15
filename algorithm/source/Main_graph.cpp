#include "../include/GRAPH/graph.hpp"

FILE *fp;
int G[MAX_VERTEX][MAX_VERTEX];
node **G_list;

int main(int argc, char *argv[]) {
	G_list = (node **)malloc(sizeof(node*) * MAX_VERTEX);

	Main_graph_list(argc, argv, G_list, fp);
}

