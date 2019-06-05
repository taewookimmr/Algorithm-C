#include "sort.hpp"

using namespace std;

namespace mySort {

	void insert(int* src, int count) {

		int temp;
		int j;
		for (int i = 1; i < count; i++) {
			temp = src[i]; // �ϴ� �ٸ� ������ �̵���Ű�� ����δ� ����.
			// src[i]�� ���ڸ���� ������ �� �ֽ��ϴ�.
			j = i;
			while (j > 0 && src[j - 1] > temp) {
				// while ó�� �����ϸ� ���ڸ��� �ٷ� �պ��� Ȯ���غ��� ���Դϴ�.
				// ���ǹ����� j > 0�� src[j-1] > temp���� �տ� �־�� �Ѵ�.
				// array outofrange(-1) error �߻������ϱ� ����
				src[j] = src[j - 1];
				j--;
				// while���� ���鼭 �� ĭ�� ������ �̵��ϸ� ũ�� �˻縦 �ϰ���.
			}
			src[j] = temp; // ���ڸ��� ����
		}
		printArray(src, count);
	}

	void select(int* src, int count) {
		int min;
		int minindex;

		for (int i = 0; i < count - 1; i++) {
			minindex = i; // �ϴ� �������� min���� ��´�.
			min = src[i]; // �ϴ� �������� min���� ��´�.
			for (int j = i + 1; j < count; j++) {
				if (min > src[j]) {
					min = src[j];
					minindex = j;
					// j���� ������Ű�� 
					// ���ǿ� ���� ���, min�� �����Ѵ�.
					// ���� �迭�� �� for���ȿ����� �������� �ʴ´�.
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