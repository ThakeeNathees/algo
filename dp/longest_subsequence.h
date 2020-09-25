#pragma once

// https://www.hackerrank.com/challenges/dynamic-programming-classics-the-longest-common-subsequence/problem

//	Input:  1 2 3 4 1
//	        3 4 1 2 1 3
//  Output: 3 4 1          <-- also 1 2 1 or 1 2 3 are valid

#if 0

int MAIN() {
	REDIRECT();

	std::vector<int> seq1, seq2;

	INPUT(int, len1); INPUT(int, len2);
	INPUT_IARR(seq1, len1); INPUT_IARR(seq2, len2);

	typedef std::vector<int> SubSeq;

	std::vector<std::vector<SubSeq>> L(2, std::vector<SubSeq>(len2));
	int _switch = 0;

	for (int i1 = 0; i1 < len1; i1++) {
		for (int i2 = 0; i2 < len2; i2++) {
			if (seq1[i1] == seq2[i2]) {
				if (i1 == 0 || i2 == 0) {
					L[_switch][i2] = { seq1[i1] };
				} else {
					L[_switch][i2] = L[(_switch + 1) % 2][i2 - 1];
					L[_switch][i2].push_back(seq1[i1]);
				}
			} else {
				if (i1 == 0 && i2 == 0) {
					L[_switch][i2].clear();
				} else if (i1 == 0) {
					L[_switch][i2] = L[_switch][i2 - 1];
				} else if (i2 == 0) {
					L[_switch][i2] = L[(_switch + 1) % 2][i2];
				} else {
					if (L[(_switch + 1) % 2][i2].size() > L[_switch][i2 - 1].size()) {
						L[_switch][i2] = L[(_switch + 1) % 2][i2];
					} else {
						L[_switch][i2] = L[_switch][i2 - 1];
					}
				}
			}
		}
		_switch = (_switch + 1) % 2;
	}

	_switch = (_switch + 1) % 2;
	for (int i = 0; i < L[_switch][len2 - 1].size(); i++) {
		PRINT(L[_switch][len2 - 1][i]); PRINT(" ");
	}

	return 0;
}

#endif