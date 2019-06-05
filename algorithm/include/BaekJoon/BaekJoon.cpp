#include "BaekJoon.hpp"

namespace BaekJoon {

	void test1000() {
		int a, b;
		std::cin >> a >> b;
		if(a > 0 && b < 10) { std::cout << (a + b); }
	}

	void test1001() {
		int a, b;
		std::cin >> a >> b;
		if (a > 0 && b < 10) { std::cout << (a - b); }
	}

	void test1002() {
		int x1 = 0, y1 = 0, r1 = 0, x2 = 0, y2 = 0, r2 = 0;
		int t = 0;

		std::cin >> t;
		int *result = new int[t];
		bool condition;

		for (int i = 0; i < t; i++) {
			std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
			std::cin.ignore();

			condition =
				(x1 >= -10000 && x1 <= 10000)
				&& (y1 >= -10000 && y1 <= 10000)
				&& (x2 >= -10000 && x2 <= 10000)
				&& (y2 >= -10000 && y2 <= 10000)
				&& (r1 >= 1 && r1 <= 10000)
				&& (r2 >= 1 && r2 <= 10000);

			if (!condition) { break; }

			int dd = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
			int rPlus = (r1 + r2)*(r1 + r2);
			int rMinus = (r1 - r2)*(r1 - r2);

			if (dd > rPlus || dd < rMinus)
				result[i] = 0;
			else if (dd == rPlus || dd == rMinus) {
				if (dd == rMinus && r1 == r2) {
					result[i] = -1;
				}
				else {
					result[i] = 1;
				}
			}
			else {
				result[i] = 2;
			}

		}

		if (!condition) {
			return;
		}
		for (int i = 0; i < t; i++) {
			std::cout << result[i] << std::endl;
		}
	}


	// test1003 관련
	int fibonacci(int num) {

		int result = 1;
		int an_2 = 1;
		int an_1 = 1;
		for (int i = 0; i <= 1; i++) {
			if (num == i)
				return 1;
		}
		for (int i = 0; i <= num - 2; i++) {
			result = an_1 + an_2;
			int temp = an_1;
			an_1 = result;
			an_2 = temp;
		}
		return result;
	}

	// test1003 관련
	int counting(int n, int x) {

		int result = 0;

		if (x == 0) {
			if (n == 0 || n == 1)
				result = 1 - n;
			else
				result = fibonacci(n - 2);
		}
		else {
			if (n == 0)
				result = 0;
			else
				result = fibonacci(n - 1);
		}

		return result;
	}

	void test1003() {

		int t = 0;
		scanf("%d", &t);
		int *result = new int[2 * t];

		for (int i = 0; i < t; i++) {
			int input = 0;
			scanf("%d", &input);
			result[0 + 2 * i] = counting(input, 0);
			result[1 + 2 * i] = counting(input, 1);
		}

		for (int i = 0; i < t; i++) {
			printf("%d %d\n", result[0 + 2 * i], result[1 + 2 * i]);
		}

		delete[] result; 
	}

}