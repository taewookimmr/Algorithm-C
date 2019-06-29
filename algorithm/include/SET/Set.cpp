#define _CRT_SECURE_NO_WARNINGS
#include "Set.hpp"

namespace Set {

	int parent[MAX_ELEMENT];
	int height[MAX_ELEMENT];

	int name2int(char c) {
		return Graph::name2int(c);
	}

	char int2name(int i) {
		return Graph::int2name(i);    
	}

	void union_set(int elem, int asso) {
		parent[elem] = asso;
	}

	/*
		return 1; when same set
		return 0; when different set
	*/
	int find_set(int elem, int asso, int flag) {
		int i = elem, j = asso;
		while (parent[i] >= 0) i = parent[i];
		while (parent[j] >= 0) j = parent[j];
		if (flag == UNION && i != j) union_set(i, j);
		return i == j;

	}

	void union_set2(int elem, int asso) {
		int t;
		if (height[elem] == height[asso]) height[asso]++;
		if (height[elem] >= height[asso]) {
			parent[asso] = elem;
		}
		else {
			parent[elem] = asso;
		}
	}


	/*
		return 1; when same set
		return 0; when different set
	*/
	int find_set2(int elem, int asso, int flag) {
		int i = elem, j = asso;
		while (parent[i] >= 0) i = parent[i];
		while (parent[j] >= 0) j = parent[j];
		if (flag == UNION && i != j) union_set2(i, j);
		return i == j;
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
			if (parent[i] == -1)printf("  ");
			else {
				printf("%c ", int2name(tree[i]));
			}
		}
		printf("\n\n");

	}

	void input_relation(FILE* fp) {
		char inform[3];
		int nelem, ninform;
		int i;

		printf("\nInput number of Elements & Information\n");
		fscanf(fp, "%d %d", &nelem, &ninform);

		for (i = 0; i < nelem; i++) parent[i] = -1;

		for (i = 0; i < ninform; i++) {
			fscanf(fp, "%s", inform);
			inform[2] = NULL; // why NULL?, just dummy?
			find_set(name2int(inform[0]), name2int(inform[1]), UNION);
		}

		print_tree(parent, nelem);
	}

	void input_relation2(FILE* fp) {
		char inform[3];
		int nelem, ninform;
		int i;

		printf("\nInput number of Elements & Information\n");
		fscanf(fp, "%d %d", &nelem, &ninform);

		for (i = 0; i < nelem; i++) parent[i] = -1;

		for (i = 0; i < ninform; i++) {
			fscanf(fp, "%s", inform);
			inform[2] = NULL; // why NULL?, just dummy?
			find_set2(name2int(inform[0]), name2int(inform[1]), UNION);
		}

		print_tree(parent, nelem);
	}

	void Main(int argc, char* argv[]) {
		FILE* fp;
		if (argc < 2) fp = stdin;
		else {
			if ((fp = fopen(argv[1], "rt")) == NULL) {
				printf("\n That file does not exist!");
				exit(1);
			}
		}

		printf("\n\nUnion & Find Operation by plane union method\n");
		input_relation(fp);

		printf("\n\nUnion & Find Operation by Path Compression\n");
		rewind(fp);
		input_relation2(fp);

		fclose(fp);
	}
}
