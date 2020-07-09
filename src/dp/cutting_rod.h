#pragma once
#include "../../algo.h"

// WARNING : Including this file more than one compilation unit will cause a compile time error
//           this repo is not well coded to organize sources intentionally (only include in main.cpp).


// https://www.geeksforgeeks.org/cutting-a-rod-dp-13/

int _max(int a, int b) {
	return max(a, b);
}

int cutting_rod(std::vector<int> p_items, int length) {

	std::vector<int> solutions;
	for (int i = 0; i <= length; i++) solutions.push_back(0);

#if ALGO_DEBUG
	set_cursor_pos(0, 0);
	for (int i = 0; i < p_items.size(); i++) {
		printf("%2i ", i + 1);
	} printf("\n");
	for (int i = 0; i < p_items.size(); i++) {
		printf("%2i ", p_items[i]);
	} printf("\n");
#endif

	for (int len = 1; len <= length; len++) {
	#if ALGO_DEBUG
		set_cursor_pos(0, 3);
		for (int i = 0; i < len; i++) {
			printf("%i : %i\n", i, solutions[i]);
		}
		getchar();
	#endif
		int solution = -1;
		for (int cut_len = 1; cut_len <= len; cut_len++) {
			solution = _max(
				solution,
				solutions[len - cut_len] + p_items[cut_len - 1]
			);
		}
		solutions[len] = solution;
	}
	return solutions[length];

#if 0 // recutsive way
	if (length == 1)  return p_items[0];
	else if (length == 0) return 0;

	int ret = -1;
	for (int i = 1; i <= length; i++) {
		ret = _max(
			ret,
			cutting_rod(p_items, length - i) + p_items[i - 1]
		);
	}
	return ret;
#endif
}

/* TEST CASE:
	std::vector<int> items;
	items.push_back(1 );    //items.push_back(3 );
	items.push_back(5);     //items.push_back(5 );
	items.push_back(8);     //items.push_back(8 );
	items.push_back(9);     //items.push_back(9 );
	items.push_back(10);    //items.push_back(10);
	items.push_back(17);    //items.push_back(17);
	items.push_back(17);    //items.push_back(17);
	items.push_back(20);    //items.push_back(20);
	printf("%i\n", cutting_rod(items, items.size()));
*/
