#pragma once
#include "include.h"

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

