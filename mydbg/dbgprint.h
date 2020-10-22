#ifndef DBGPRINT_H
#define DBGPRINT_H

#include "core.h"

class Printable {
public:
	struct Pointer { // TODO: constructor from const char*
	public:
		Printable* ptr = nullptr;
		Pointer(Printable& ptr) : ptr(&ptr) {}
		Pointer(Printable* ptr) : ptr(ptr) {}
	};
	virtual void dbprint() = 0;
	virtual void flush() {}
};

template<typename... Args>
void dbprint(Args&... args) {
	if (TesterGlobals::print_cls) clear_console();
	_dbprint_internal(args...);
	if (TesterGlobals::print_pause) getchar();
}

template<typename... Args>
void _dbprint_internal(Printable::Pointer pp, Args&... args) {
	pp.ptr->dbprint();
	pp.ptr->flush();
	_dbprint_internal(args...);
}

template<typename... Args>
void _dbprint_internal(Printable::Pointer pp) {
	pp.ptr->dbprint();
	pp.ptr->flush();
}

//template<typename T>
class iVecPrinter : public Printable {
	std::vector<int>* src;
	std::vector<int> copy;
	int ind = -1, l = -1, r = -1;
	std::map<int, Color> elem_color_override;

	int elem_width = 2;
public:
	iVecPrinter(std::vector<int>* src) : src(src), copy(*src) {}

	iVecPrinter& operator()(int p_ind) { ind = p_ind; return *this; }
	iVecPrinter& operator()(int p_l, int p_r, int p_ind = -1) { l = p_l; r = p_r; ind = p_ind; return *this; }
	virtual void flush() override { l = -1, r = -1, ind = -1; }

	iVecPrinter& add_color(int ind, Color color) { elem_color_override[ind] = color; return *this; }
	iVecPrinter& remove_color(int ind) { elem_color_override.erase(ind); return *this; }
	iVecPrinter& clear_color() { elem_color_override.clear(); return *this; }

	void dbprint() override;

};

class iVec2dPrinter : public Printable {
	std::vector<std::vector<int>>* src;
	std::vector<std::vector<int>> copy;
	int openh = -1, openw = -1;   // [
	int closeh = -1, closew = -1; // ]
	int indh = -1, indw = -1; // single index h, w
	std::map<std::pair<int, int>, Color> elem_color_override;

	int elem_width = 2;
public:
	iVec2dPrinter(std::vector<std::vector<int>>* src) : src(src), copy(*src) {}

	iVec2dPrinter& operator()(int p_indh, int p_indw) { indh = p_indh; indw = p_indw; return *this; }
	iVec2dPrinter& operator()(int oh, int ow, int ch, int cw) { openh = oh, openw = ow, closeh = ch, closew = cw; return *this; }
	virtual void flush() override { openh = -1, openw = -1, closeh = -1, closew = -1, indh = -1, indw = -1; }

	iVec2dPrinter& add_color(int indh, int indw, Color color) { elem_color_override[{ indh, indw }] = color; return *this; }
	iVec2dPrinter& remove_color(int indh, int indw) { elem_color_override.erase({ indh, indw }); return *this; }
	iVec2dPrinter& clear_color() { elem_color_override.clear(); return *this; }

	void dbprint() override;
};


#endif // DBGPRINT_H