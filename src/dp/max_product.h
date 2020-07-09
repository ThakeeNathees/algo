#pragma once
#include "../../algo.h"

// WARNING : Including this file more than one compilation unit will cause a compile time error
//           this repo is not well coded to organize sources intentionally (only include in main.cpp).


// https://www.geeksforgeeks.org/maximum-product-cutting-dp-36/

int _max4(int a, int b, int c, int d) {
	return max(a, max(b, max(c, d)));
}

int max_product(int n) {
	std::vector<int> solutions(n + 1);

	solutions[0] = 0;
	solutions[1] = 1;
	solutions[2] = 1;

	for (int i = 3; i <= n; i++) {
		int j = 1;
		int solution = 0;
	#if ALGO_DEBUG
		set_cursor_pos(0, 0);
		for (int k = 0; k < i; k++) {
			printf("%i : %i\n", k, solutions[k]);
		}
		getchar();
		//if (i == n) __debugbreak();
	#endif
		while (j <= i / 2) {
			solution = _max4(
				solution,
				solutions[j] * (i - j),
				j * solutions[i - j],
				j * (i - j)
			);
			j++;
		}
		solutions[i] = solution;
	}
#if ALGO_DEBUG
	printf("%i : %i\n", n, solutions[n]);
	getchar();
#endif
	return solutions[n];
}

/* TEST CASE:
	RUN(max_product(10));
*/

