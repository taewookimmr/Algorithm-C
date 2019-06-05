#include "sort.hpp"

using namespace std;

namespace mySort {

	void insert(int* src, int count) {

		int temp;
		int j;
		for (int i = 1; i < count; i++) {
			temp = src[i]; // 일단 다른 곳으로 이동시키고 비워두는 느낌.
			// src[i]가 빈자리라고 생각할 수 있습니다.
			j = i;
			while (j > 0 && src[j - 1] > temp) {
				// while 처음 시작하면 빈자리의 바로 앞부터 확인해보는 것입니다.
				// 조건문에서 j > 0이 src[j-1] > temp보다 앞에 있어야 한다.
				// array outofrange(-1) error 발생가능하기 때문
				src[j] = src[j - 1];
				j--;
				// while문을 돌면서 한 칸씩 앞으로 이동하며 크기 검사를 하겠죠.
			}
			src[j] = temp; // 빈자리에 삽입
		}
		printArray(src, count);
	}

	void select(int* src, int count) {
		int min;
		int minindex;

		for (int i = 0; i < count - 1; i++) {
			minindex = i; // 일단 시작점을 min으로 잡는다.
			min = src[i]; // 일단 시작점을 min으로 잡는다.
			for (int j = i + 1; j < count; j++) {
				if (min > src[j]) {
					min = src[j];
					minindex = j;
					// j값을 증가시키며 
					// 조건에 맞을 경우, min을 갱신한다.
					// 원본 배열을 이 for문안에서는 갱신하지 않는다.
				}
			}
			src[minindex] = src[i];
			src[i] = min;
			printArray(src, count);
		}

	}

	void printArray(int *src, int count) {
		for (int i = 0; i < count; i++) {
			cout << src[i] << " ";
		}   cout << endl;
	}

	void Main_sort() {

		int src[] = { 3, 4, 7, 9, 2, 1, 10, 300, 200, 90 };
		select(src, sizeof(src) / sizeof(int));

	}

}