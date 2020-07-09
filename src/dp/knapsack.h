#pragma once
#include "../../algo.h"

// WARNING : Including this file more than one compilation unit will cause a compile time error
//           this repo is not well coded to organize sources intentionally (only include in main.cpp).

int knapsack(std::vector<std::pair<int, int>> p_items, int p_max_weight) {
	std::vector<std::vector<int>> solutions;
	for (int i = 0; i < p_items.size(); i++) {
		solutions.push_back(std::vector<int>(p_max_weight + 1));
	}

	for (int item = 0; item < p_items.size(); item++) {
		for (int weight = 0; weight <= p_max_weight; weight++) {

#if ALGO_DEBUG
			set_cursor_pos(0, 0);
			printf("val  wt   |");
			for (int j = 0; j < p_max_weight + 1; j++) {
				printf(" %2i  ", j);
			} printf("(weights)\n-----------------------------------------------\n");
			for (int i = 0; i <= item; i++) {
				printf("(%2i, %2i) | ", p_items[i].first, p_items[i].second);
				for (int j = 0; j <= p_max_weight; j++) {
					if (i == item && j == weight) printf("[%2i] ", solutions[i][j]);
					else printf(" %2i  ", solutions[i][j]);
				} printf("\n");
			}
			getchar();
#endif
			int solution = 0;
			if (weight == 0) solution = 0;
			else if (item == 0) {
				if (p_items[item].second > weight) solution = 0;
				else solution = p_items[item].first;
			} else {
				if (p_items[item].second > weight) {
					solution = solutions[item - 1][weight];
				} else {
					solution = max(
						solutions[item - 1][weight],
						p_items[item].first + solutions[item - 1][weight - p_items[item].second]
					);
				}
			}
			solutions[item][weight] = solution;
		}
	}
#if ALGO_DEBUG
	set_cursor_pos(0, 0);
	printf("val  wt   |");
	for (int j = 0; j < p_max_weight + 1; j++) {
		printf(" %2i  ", j);
	} printf("(weights)\n-----------------------------------------------\n");
	for (int i = 0; i < solutions.size(); i++) {
		printf("(%2i, %2i) | ", p_items[i].first, p_items[i].second);
		for (int j = 0; j <= p_max_weight; j++) {
			if (i == solutions.size() && j == p_max_weight + 1) printf("[%2i] ", solutions[i][j]);
			else printf(" %2i  ", solutions[i][j]);
		} printf("\n");
	}
	getchar();
#endif
	return 0;
}

/* TEST CASE:
	std::vector<std::pair<int, int>> items;
	items.push_back(std::make_pair<int, int>(1, 1));
	items.push_back(std::make_pair<int, int>(4, 3));
	items.push_back(std::make_pair<int, int>(5, 4));
	items.push_back(std::make_pair<int, int>(7, 5));
	RUN(knapsack(items, 7));
*/