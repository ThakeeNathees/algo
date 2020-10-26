#ifndef DBGPRINT_H
#define DBGPRINT_H

#include "core.h"
#include "dbgtypes.h"

class Printable {
public:
	struct Pointer { // TODO: constructor from const char*
	public:
		Printable* ptr = nullptr;
		Pointer(Printable& ptr) : ptr(&ptr) {}
		Pointer(Printable* ptr) : ptr(ptr) {}
	};

	virtual void* get_src() { return nullptr; };
	virtual void dprint() = 0;
	virtual void flush() {}
};

template<typename... Args>
void dprint(Args&... args) {
	if (TesterGlobals::print_cls) clear_console();
	_dprint_internal(args...);
	if (TesterGlobals::print_pause) getchar();
}

template<typename... Args>
void _dprint_internal(Printable::Pointer pp, Args&... args) {
	pp.ptr->dprint();
	pp.ptr->flush();
	_dprint_internal(args...);
}

template<typename... Args>
void _dprint_internal(Printable::Pointer pp) {
	pp.ptr->dprint();
	pp.ptr->flush();
}

template<typename T>
class dbgvec : public Printable {
	std::vector<T>* src;
	std::vector<T> copy;
	int ind = -1, l = -1, r = -1;
	std::map<int, Color> elem_color_override;

	int elem_width = 2;
public:
	dbgvec(std::vector<T>& src) : src(&src), copy(src) {}
	dbgvec(std::vector<T>* src) : src(src), copy(*src) {}

	dbgvec& operator()(int p_ind) { ind = p_ind; return *this; }
	dbgvec& operator()(int p_l, int p_r, int p_ind = -1) { l = p_l; r = p_r; ind = p_ind; return *this; }
	virtual void flush() override { l = -1, r = -1, ind = -1; }

	dbgvec& add_color(int ind, Color color) { elem_color_override[ind] = color; return *this; }
	dbgvec& remove_color(int ind) { elem_color_override.erase(ind); return *this; }
	dbgvec& clear_color() { elem_color_override.clear(); return *this; }
	virtual void* get_src() { return src; };

	void dprint() override {
		printf("[");
		for (int i = 0; i < (int)src->size(); i++) {
			if (i) printf((i != r) ? ", " : " ");

			int width_reduction = 0;

			if (i == l) cprint("[", TesterGlobals::index_color), width_reduction++;
			if (i == ind) cprint("#", TesterGlobals::index_color), width_reduction++;

			Color elem_color = Color::L_WHITE;
			T elem = (*src)[i];
			if (i < copy.size()) {
				if (copy[i] != elem) copy[i] = elem, elem_color = TesterGlobals::changed_color;
			} else { // new element inserted.
				copy.push_back(elem);
				elem_color = TesterGlobals::changed_color;
			}
			std::map<int, Color>::iterator it = elem_color_override.find(i);
			if (it != elem_color_override.end()) elem_color = it->second;

			std::string elem_str = std::to_string(elem);
			while (elem_str.size() < elem_width - width_reduction) elem_str = " " + elem_str;
			cprint(elem_str.c_str(), elem_color);

			if (i + 1 == r) cprint("]", TesterGlobals::index_color);
		}
		printf(" ]\n");
	}

};

template<typename T>
class dbgvec2d : public Printable {
	std::vector<std::vector<T>>* src;
	std::vector<std::vector<T>> copy;
	int openh = -1, openw = -1;   // [
	int closeh = -1, closew = -1; // ]
	int indh = -1, indw = -1; // single index h, w
	std::map<std::pair<int, int>, Color> elem_color_override;

	int elem_width = 2;
public:
	dbgvec2d(std::vector<std::vector<T>>& src) : src(&src), copy(src) {}
	dbgvec2d(std::vector<std::vector<T>>* src) : src(src), copy(*src) {}

	dbgvec2d& operator()(int p_indh, int p_indw) { indh = p_indh; indw = p_indw; return *this; }
	dbgvec2d& operator()(int oh, int ow, int ch, int cw) { openh = oh, openw = ow, closeh = ch, closew = cw; return *this; }
	virtual void flush() override { openh = -1, openw = -1, closeh = -1, closew = -1, indh = -1, indw = -1; }

	dbgvec2d& add_color(int indh, int indw, Color color) { elem_color_override[{ indh, indw }] = color; return *this; }
	dbgvec2d& remove_color(int indh, int indw) { elem_color_override.erase({ indh, indw }); return *this; }
	dbgvec2d& clear_color() { elem_color_override.clear(); return *this; }
	virtual void* get_src() { return src; };

	void dprint() override {
		printf("[");
		for (int h = 0; h < (int)src->size(); h++) {
			printf(h ? " [" : "["); // align with the very first '['

			for (int w = 0; w < (int)(*src)[0].size(); w++) {
				if (w) printf((w != closew || h != closeh) ? ", " : " ");

				int width_reduction = 0;

				if (h == openh && w == openw) cprint("[", TesterGlobals::index_color), width_reduction++;
				if (h == indh && w == indw) cprint("#", TesterGlobals::index_color), width_reduction++;

				Color elem_color = Color::L_WHITE;
				T elem = (*src)[h][w];
				if (h < copy.size()) {
					if (w < copy[h].size()) {
						if (copy[h][w] != elem) copy[h][w] = elem, elem_color = TesterGlobals::changed_color;
					} else {
						copy[h].push_back(elem);
						elem_color = TesterGlobals::changed_color;
					}
				} else {
					copy.push_back({ elem });
					elem_color = TesterGlobals::changed_color;
				}
				std::map<std::pair<int, int>, Color>::iterator it = elem_color_override.find({ h, w });
				if (it != elem_color_override.end()) elem_color = it->second;

				std::string elem_str = std::to_string(elem);
				while (elem_str.size() < elem_width - width_reduction) elem_str = " " + elem_str;
				cprint(elem_str.c_str(), elem_color);

				if (h == closeh && w + 1 == closew) cprint("]", TesterGlobals::index_color);
			} printf((h ^ src->size() - 1) ? " ]\n" : " ]");
		} printf("]\n");
	}
};


//////////////////////////////////////////////////////////////////////////////////////////////////

#endif // DBGPRINT_H