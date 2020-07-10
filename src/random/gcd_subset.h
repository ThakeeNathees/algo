#pragma once

#include "../../algo.h"

// https://www.geeksforgeeks.org/count-number-of-subsets-of-a-set-with-gcd-equal-to-a-given-number/

void gcd_subset(std::vector<int> gcd, std::vector<int> nums) {
	std::unordered_map<int, int> frequency;
	std::unordered_map<int, int> subsets;
	int num_max = 0;
	for (int num : nums) {
		frequency[num]++;
		if (num > num_max) num_max = num;
	}

	for (int i = num_max; i >= 1; i--) {
		int factor_count = frequency[i]; // these many numbers can divided by i
		int subtract_subsets = 0;

		for (int j = 2; i * j <= num_max; j++) {
			factor_count += frequency[i * j];
			subtract_subsets += subsets[i * j];
		}
		subsets[i] = (1 << factor_count) - 1 - subtract_subsets;
	}
	for (int num : gcd) {
		printf("%i\n", subsets[num]);
	}
}

