#pragma once
#include "../algo.h"

// WARNING : Including this file more than one compilation unit will cause a compile time error
//           this repo is not well coded to organize sources intentionally (only include in main.cpp).

std::vector<int> z_function(const std::string& str) {
	int n = str.size();
	std::vector<int> z(n);
	z[0] = 0;

#if ALGO_DEBUG
	std::vector<int> copied;
#endif

	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
	#if ALGO_DEBUG
		set_cursor_pos(0, 0);
		for (int j = 0; j < str.size(); j++) {
			if (j == l) printf("[");
			if (j == r) printf("] ");
			printf("%c ", str[j]);
		} printf((r == n) ? "]\n" : "\n");
		for (int j = 0; j < i; j++) {
			if (j == l) printf(" ");
			if (j == r) printf("  ");
			printf("  ");
		} printf((r == i) ? "  ^\n" : "^\n");
		for (int j = 0; j < i; j++) {
			if (std::find(copied.begin(), copied.end(), j) != copied.end())
				cprint(std::to_string(z[j]).append(" ").c_str(), Color::D_GREEN);
			else
				printf("%i ", z[j]);
		}
		printf("\n");
		getchar();
	#endif

		if (i >= r) {

			l = r = i;
			while (r < n && str[r - l] == str[r]) r++;
			z[i] = r - l;

		} else {

			if (i + z[i - l] < r) {
				z[i] = z[i - l];
			#if ALGO_DEBUG
				copied.push_back(i);
			#endif
			} else {
				l = i;
				while (r < n && str[r - l] == str[r]) r++;
				z[i] = r - l;
			}
		}
	}
	return z;
}


