#include "heap.hpp"

namespace Heap{

	void upheap(int heap[], int k) {
		int v;
		v = heap[k];
		heap[0] = SENTINEL;
		while (heap[k / 2] <= v) {
			heap[k] = heap[k / 2];
			k /= 2;
		}
		heap[k] = v;
	}
	void downheap(int heap[], int n, int k) {
		int i, v;
		v = heap[k];
		while (k <= n / 2) {
			// k�� ���� ����� ��쿡 ���ؼ�
			i = k << 1;
			if (i < n && heap[i] < heap[i + 1]) i++;
			// �ڽ� �� ū �ڽ��� �����Ѵ�.
			if (v <= heap[i]) break; // �� ������ �����Ǹ� whilescape
			heap[k] = heap[i]; // heap ������ �������� ������ ����
			k = i;
		}
		heap[k] = v;
	}
	
	void insert(int heap[], int* n, int v) {
		heap[++(*n)] = v;
		upheap(heap, *n);
	}

	int extract(int heap[], int* n) {
		int v = heap[1]; // heap[1]�� �Ѹ�
		heap[1] = heap[(*n)--];
		downheap(heap, *n, 1);
		return 0;
	}

	/*
		heap_sort�� �μ��� ������ heap[]�� "���� ����" ����� ä������ ���;� �Ѵ�.
	*/
	void heap_sort(int heap[], int n) {
		int i;
		int hn = 0; // ���� ��� ��, n�� �迭�� ũ��

		for (i = 1; i <= n; i++)
			insert(heap, &hn, heap[i]);

		for (i = hn; i >= 1; i--)
			heap[i] = extract(heap, &hn);
	}


	void heap_sort2(int heap[], int n) {
		int k, t;
		for (k = n / 2; k >= 1; k--)
			downheap(heap, n, k);

		while (n > 1) {
			t = heap[1];
			heap[1] = heap[n];
			heap[n] = t;
			downheap(heap, --n, 1);
		}
	}
}
