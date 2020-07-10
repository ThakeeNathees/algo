#pragma once

#include "../../algo.h"

// https://www.hackerrank.com/contests/moraxtreme-4-0-initial-round/challenges/dining-philosophers/problem

class SortedVector {
public:
	std::vector<int> _data;
	void insert(int val) {
		if (_data.size() == 0) {
			_data.push_back(val);
			return;
		}
		int i, l = 0, r = _data.size() - 1;
		if (val < _data[l]) { _data.insert(_data.begin(), val); return; }
		if (_data[r] < val) { _data.push_back(val); return; }

		while (true) {
			i = (l + r) / 2;
			if (i == l) {
				_data.insert(_data.begin() + i + 1, val);
				return;
			}
			if (val < _data[i]) r = i;
			else if (_data[i] < val) l = i;
			else {
				_data.insert(_data.begin() + i, val);
				return;
			}
		}
	}
	void remove(int val) {
		if (_data[0] == val) { _data.erase(_data.begin()); return; }
		if (_data[_data.size() - 1] == val) { _data.erase(_data.end() - 1); return; }

		int i, l = 0, r = _data.size() - 1;
		while (true) {
			i = (l + r) / 2;
			if (i == l) {
				_data.erase(_data.begin() + i);
				return;
			}
			if (val < _data[i]) r = i;
			else if (_data[i] < val) l = i;
			else {
				_data.erase(_data.begin() + i);
				return;
			}
		}
	}
};


int main() {

	int p, q, r;
	std::cin >> p >> q >> r;

	std::vector<int> pid;
	for (int i = 0; i < p; i++) {
		int id;
		std::cin >> id;
		pid.push_back(id);
	}

	int result = 0;
	SortedVector group;
	for (int i = 0; i < q; i++) {
		group.insert(pid[i]);
	}
	result = group._data[r - 1];

	for (int i = 0; i < p; i++) {
		group.remove(pid[i]);
		group.insert(pid[(i + q) % p]);

		if (group._data[r - 1] < result) result = group._data[r - 1];
	}
	printf("%i\n", result);

	return 0;
}
