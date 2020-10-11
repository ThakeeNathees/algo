#pragma once
#include "include.h"

struct SwitchIndex {
	int _ind = 0;
	inline int ind() const { return _ind; }
	inline int incr() { int ret = _ind; _ind = (_ind + 1) % 2; return ret; }
	inline int prev() const { return (_ind + 1) % 2; }
};

struct CycleIndex {
	int _size, _ind = 0;
	CycleIndex(int size) : _size(size) {}
	inline int ind() const { return _ind; }
	inline int incr() { int ret = _ind; _ind = (_ind + 1) % _size; return ret; }
	inline int prev(int x = 1) { return next(-x); }
	inline int next(int x = 1) {
		if (x == 0) return _ind;
		else if (x < 0) { int k = ((-x) / _size) + 1; return (k * _size + x) % _size; } else return (_ind + x) % _size;
	}
};
