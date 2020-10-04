#pragma once


struct SwitchIndex {
	int _ind = 0;
	inline int ind() const { return _ind; }
	inline int next() const { return (_ind + 1) % 2; }
	inline int prev() const { return next(); }
	inline void incr() { _ind = (_ind + 1) % 2; }
};
