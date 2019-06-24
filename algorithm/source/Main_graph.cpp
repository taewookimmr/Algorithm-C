#include "../include/GRAPH/graph.hpp"
#include "../include/DQS/DoubleQueueStack.hpp"
#include <stdlib.h>

FILE *fp;
int G[MAX_VERTEX][MAX_VERTEX];
node** G_list;


int main(int argc, char *argv[]) {
	G_list = (node **)malloc(sizeof(node*) * MAX_VERTEX);
	// 각 요소별로 멤록안해도 된다. 뒷단에서 해준다.
	Main_graph_list(argc, argv, G_list, fp);
	//Main_graph(argc, argv, G, fp);
}

