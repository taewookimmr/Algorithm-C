#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../GlobalVariables/GV_Graph.hpp"
#include "../GRAPH/Graph.hpp"

namespace Set {
	int name2int(char c);
	char int2name(int i);
	void union_set(int elem, int asso);
	int find_set(int elem, int asso, int flag);
	void union_set2(int elem, int asso);
	int find_set2(int elem, int asso, int flag);
	void print_tree(int tree[], int n);
	void input_relation(FILE* fP);
	void input_relation2(FILE* fp);
	void Main(int argc, char* argv[]);
}
