#pragma once

#include "../../algo.h"

// WARNING : Including this file more than one compilation unit will cause a compile time error
//           this repo is not well coded to organize sources intentionally (only include in main.cpp).


int longest_palindromic_subsequence(const std::string& str) {
	std::vector<std::vector<int>> lengths;
	for (int i = 0; i < str.size(); i++) {
		lengths.push_back(std::vector<int>(str.size()));
	}

	// as[d]f123fdsa <-- len ==1 -> longest subsequence len = 1
	for (int i = 0; i < str.size(); i++) {
		lengths[i][i] = 1;
	}

	for (int len = 2; len <= str.size(); len++) {
		for (int l = 0; l <= str.size() - len; l++) {
			int r = l + len;
		#ifdef ALGO_DEBUG
			set_cursor_pos(0, 0);
			for (int i = 0; i < str.size(); i++) {
				if (i == l) printf("[");
				printf("%c ", str[i]);
				if (i + 1 == r) printf("] ");
			} printf("\n");

			for (int i = 0; i < str.size(); i++) {
				for (int j = 0; j < str.size(); j++) {
					if (i == l - 1 && j == r - 2) {
						char buff[10]; buff[9] = 0;
						snprintf(buff, 10, "%2i ", lengths[i][j]);
						cprint(buff, Color::D_GREEN);
					} else printf("%2i ", lengths[i][j]);
				} printf("\n");
			}

			getchar();
		#endif

			// asdf1[22]3asdf
			if (str[l] == str[r - 1] && len == 2) {
				lengths[l][r - 1] = 2;
			} else if (str[l] == str[r - 1]) {
				lengths[l][r - 1] = lengths[l + 1][r - 2] + 2;
			} else {
				lengths[l][r - 1] = max(
					lengths[l][r - 2],
					lengths[l + 1][r - 1]
				);
			}
		}
	}
	return lengths[0][str.size() - 1];
}
