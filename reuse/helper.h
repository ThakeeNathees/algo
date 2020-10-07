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

struct Tire {
	char c = 0;
	bool is_end = true;
	Tire* chars[26] = { nullptr };

	Tire() {}
	Tire(char c, bool is_end = false) : c(c), is_end(is_end) {}
	void unsafe_delete(char c) { // cause memory leak, but fast.
		if (chars[c - 'a']) delete chars[c - 'a'];
		chars[c - 'a'] = nullptr;
	}

	void insert(const char* str) {
		int ind = *str - 'a';
		if (chars[ind] == nullptr) chars[ind] = new Tire(*str);
		if (*(++str) == 0) chars[ind]->is_end = true;
		else chars[ind]->insert(str);
	}
	void print() const { printf("Tire = [\n"); _print("", this); printf("]\n"); }

private:
	void _print(std::string s, const Tire* what) const {
		for (int i = 0; i < 26; i++) {
			if (what->chars[i]) {
				if (what->chars[i]->is_end) printf("\t%s,\n", (s + what->chars[i]->c).c_str());
				_print(s + what->chars[i]->c, what->chars[i]);
			}
		}
	}
};

