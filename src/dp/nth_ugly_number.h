#pragma once
#include "../../algo.h"

// WARNING : Including this file more than one compilation unit will cause a compile time error
//           this repo is not well coded to organize sources intentionally (only include in main.cpp).


// https://www.geeksforgeeks.org/ugly-numbers/
// Ugly numbers are numbers whose only prime factors are 2, 3 or 5. 
// The sequence 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, … shows the first 11 ugly numbers. By convention, 1 is included.
// Given a number n, the task is to find n’th Ugly number

int _min3(int a, int b, int c) {
	return min(a, min(b, c));
}

int nth_ugly_number(int n) {
	std::vector<int> ugly(n);
	ugly[0] = 1;

	int i2, i3, i5;
	i2 = i3 = i5 = 0;

	for (int i = 1; i < n; i++) {
		ugly[i] = _min3(
			ugly[i2] * 2,
			ugly[i3] * 3,
			ugly[i5] * 5
		);

		if (ugly[i] == ugly[i2] * 2) i2++;
		if (ugly[i] == ugly[i3] * 3) i3++;
		if (ugly[i] == ugly[i5] * 5) i5++;
	}

	return ugly[n - 1];

}
