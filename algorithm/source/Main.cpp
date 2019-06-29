#include "../include/GRAPH/graph.hpp"
#include "../include/SET/Set.hpp"

#define __GRAPH__			100
#define __WGRAPH_PFS__		101
#define __WGRAPH_KRUSKAL__	102
#define __SET__				103


#define __MAIN__ __WGRAPH_KRUSKAL__

int main(int argc, char* argv[]) {

	#if __MAIN__ == __GRAPH__
		argc = 2;
		argv[0] = (char*)"algorithm.exe";
		argv[1] = (char*)"../Debug/res/graph.txt";
		Graph::Main_graph_list(argc, argv);
	#endif

	#if __MAIN__ == __WGRAPH_PFS__
		argc = 2;
		argv[0] = (char*)"algorithm.exe";
		argv[1] = (char*) "../Debug/res/wgraph.txt";
		WeightGraph::PFS::Main(argc, argv);
	#endif

	#if __MAIN__ == __WGRAPH_KRUSKAL__
			argc = 2;
			argv[0] = (char*)"algorithm.exe";
			argv[1] = (char*) "../Debug/res/wgraph.txt";
			WeightGraph::Kruskal::Main(argc, argv);
	#endif

	#if __MAIN__ == __SET__
		argc = 2;
		argv[0] = (char*)"algorithm.exe";
		argv[1] = (char*) "../Debug/res/set.txt";
		Set::Main(argc, argv);
	#endif




}


