#pragma once
#include "include.h"

std::vector<int> z_function(const std::string& str) {
	int n = str.size();
	std::vector<int> z(n);
	z[0] = 0;

	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {

		if (i >= r) {
			l = r = i;
			while (r < n && str[r - l] == str[r]) r++;
			z[i] = r - l;

		} else {

			if (i + z[i - l] < r) {
				z[i] = z[i - l];
			} else {
				l = i;
				while (r < n && str[r - l] == str[r]) r++;
				z[i] = r - l;
			}
		}
	}
	return z;
}