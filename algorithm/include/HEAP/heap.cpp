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
			// k가 내부 노드인 경우에 한해서
			i = k << 1;
			if (i < n && heap[i] < heap[i + 1]) i++;
			// 자식 중 큰 자식을 선택한다.
			if (v <= heap[i]) break; // 힙 조건이 만족되면 whilescape
			heap[k] = heap[i]; // heap 족ㄴ을 만족하지 않으면 삽입
			k = i;
		}
		heap[k] = v;
	}
	
	void insert(int heap[], int* n, int v) {
		heap[++(*n)] = v;
		upheap(heap, *n);
	}

	int extract(int heap[], int* n) {
		int v = heap[1]; // heap[1]은 뿌리
		heap[1] = heap[(*n)--];
		downheap(heap, *n, 1);
		return 0;
	}

	/*
		heap_sort의 인수로 들어오는 heap[]은 "정렬 전의" 값들로 채워져서 들어와야 한다.
	*/
	void heap_sort(int heap[], int n) {
		int i;
		int hn = 0; // 힙의 노드 수, n은 배열의 크기

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
