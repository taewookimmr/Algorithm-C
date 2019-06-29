#pragma once
#include "../GlobalVariables/gv.hpp"

namespace Heap {
	void upheap(int heap[], int k);
	void downheap(int heap[], int n, int k);
	void insert(int heap[], int* n, int v);
	int extract(int heap[], int* n);
	void heap_sort(int heap[], int n);
	void heap_sort2(int heap[], int n);
}
