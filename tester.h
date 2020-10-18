//------------------------------------------------------------------------------
// MIT License
//------------------------------------------------------------------------------
// 
// Copyright (c) 2020 Thakee Nathees
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//------------------------------------------------------------------------------

// TODO:

#ifndef TESTER_H
#define TESTER_H

#include <bits/stdc++.h>

#define _TESTING
#define MAIN _main
#define TEST main

#define STRING(x) #x
#define STRINGIFY(x) STRING(x)

#define CHECK(m_result, m_expected)                                  \
do {                                                                 \
	printf("TEST (line:" STRINGIFY(__LINE__) "): ");                 \
	if (m_result != m_expected) {                                    \
		cprint("FAILURE\n", Color::L_RED);                           \
		printf("\tEXPECTED : %s\n", _to_string(m_expected).c_str()); \
		printf("\tRESULT   : %s\n", _to_string(m_result).c_str());   \
	} else {                                                         \
		cprint("SUCCESS\n", Color::L_GREEN);                         \
	}                                                                \
}  while (false)

#define TIMER_START() TesterGlobals::timer_line = __LINE__, TesterGlobals::timer_t0 = std::chrono::steady_clock::now()
#define TIMER_END()                                                                             \
	printf("TIMER (line:%i): ", TesterGlobals::timer_line),                                     \
	TesterGlobals::timer_duration = std::chrono::steady_clock::now() - TesterGlobals::timer_t0, \
	cprint(_to_string(TesterGlobals::timer_duration.count() * 1000).append(" ms\n").c_str(), Color::L_SKYBLUE)


#define REDIRECT()                                                       \
	class Redirect {									                 \
		std::istringstream isstream;					                 \
		std::ostringstream osstream;					                 \
		std::streambuf* istream_buf;					                 \
		std::streambuf* ostream_buf;					                 \
	public:												                 \
		Redirect() {									                 \
			istream_buf = std::cin.rdbuf();				                 \
			isstream = std::istringstream(TesterGlobals::_INPUT_BUFF);	 \
			std::cin.rdbuf(isstream.rdbuf());			                 \
			ostream_buf = std::cout.rdbuf();			                 \
			osstream = std::ostringstream(TesterGlobals::_OUTPUT_BUFF);  \
			std::cout.rdbuf(osstream.rdbuf());			                 \
		}												                 \
		~Redirect() {									                 \
			TesterGlobals::_OUTPUT_BUFF = strip(osstream.str());		 \
			std::cin.rdbuf(istream_buf);				                 \
			std::cout.rdbuf(ostream_buf);				                 \
		}												                 \
	};													                 \
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr); Redirect redirect

#define TEST_MAIN(m_input_buff, m_output_buff)                           \
	_EXPECTED_OUTPUT = strip(m_output_buff);                             \
	TesterGlobals::_INPUT_BUFF = strip(m_input_buff);                    \
	TesterGlobals::_OUTPUT_BUFF = "";                                    \
	MAIN();                                                              \
	printf("LINE [" TOSTRING(__LINE__) "]: ");                           \
	if (_OUTPUT_BUFF != _EXPECTED_OUTPUT ) {                             \
		cprint("FAILURE\n", Color::L_RED);                               \
		cprint("\tEXPECTED : ", Color::L_YELLOW); printf("%s\n", TesterGlobals::_EXPECTED_OUTPUT .c_str());  \
		cprint("\tRESULT   : ", Color::L_YELLOW); printf("%s\n", TesterGlobals::_OUTPUT_BUFF.c_str());       \
	} else {                                                             \
		cprint("SUCCESS\n", Color::L_GREEN);                             \
	}

enum class Color {
	BLACK = 0,

	L_BLUE = 1,
	L_GREEN = 2,
	L_SKYBLUE = 3,
	L_RED = 4,
	L_PINK = 5,
	L_YELLOW = 6,
	L_WHITE = 7,
	L_GRAY = 8,

	D_BLUE = 9,
	D_GREEN = 10,
	D_SKYBLUE = 11,
	D_RED = 12,
	D_PINK = 13,
	D_YELLOW = 14,
	D_WHITE = 15,
};

class TesterGlobals { // a static class for globals.
public:
	// timer variables
	static int timer_line;
	static std::chrono::steady_clock::time_point timer_t0;
	static std::chrono::duration<double> timer_duration;

	// IO variables
	static std::string _INPUT_BUFF;
	static std::string _OUTPUT_BUFF;
	static std::string _EXPECTED_OUTPUT;

	// dbprint
	static bool print_cls; // clear screen before print
	static bool print_pause; // will pause after each draw.
	static Color index_color; // 1 2 [3] #4 5  color to indicate index
	static Color changed_color;
};

std::string strip(const std::string& str);
void clear_console();
void set_cursor_pos(int column, int line);
void cprint(const char* p_msg, Color p_fg, Color p_bg = Color::BLACK);

template <typename T>
std::string _to_string(T value) {
	if constexpr (std::is_arithmetic<T>::value) {
		return std::to_string(value);
	} else if constexpr (std::is_same<T, std::string>::value || std::is_same<T, const std::string&>::value) {
		return value;
	} else if constexpr (std::is_same<T, std::vector<int>>::value || std::is_same<T, std::vector<long>>::value ||
		std::is_same<T, std::vector<float>>::value || std::is_same<T, std::vector<double>>::value ) {
		std::string ret = "[ ";
		for (size_t i = 0; i < value.size(); i++) {
			if (i != 0) ret += ", ";
			ret += std::to_string(value[i]);
		}
		return ret + " ]";
	} else if constexpr (std::is_same<T, const char*>::value) {
		return value;
	}
}

// DBPRINT ////////////////////////////////////////////////////////////////////////////////

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
class VecPrinter : public Printable {
	std::vector<int>* src;
	std::vector<int> copy;
	int ind, l, r;
	std::map<int, Color> elem_color_override;

	int elem_width = 2;
public:
	VecPrinter(std::vector<int>* src) : src(src), copy(*src) {}

	VecPrinter& operator()(int p_ind) { ind = p_ind; return *this; }
	VecPrinter& operator()(int p_l, int p_r, int p_ind = -1) { l = p_l; r = p_r; ind = p_ind; return *this; }
	virtual void flush() override { l = -1, r = -1, ind = -1; }

	VecPrinter& add_color(int ind, Color color) { elem_color_override[ind] = color; return *this; }
	VecPrinter& remove_color(int ind) { elem_color_override.erase(ind); return *this; }

	void dbprint() override;

};

#endif // TESTER_H


//--------------- IMPLEMENTATIONS -------------------

#if defined(TESTER_IMPL)

//include "core.h"

#ifdef _WIN32
	#define NOMINMAX
	#include <windows.h>
#else
	#include <unistd.h>
#endif

int TesterGlobals::timer_line;
std::chrono::steady_clock::time_point TesterGlobals::timer_t0;
std::chrono::duration<double> TesterGlobals::timer_duration;

std::string TesterGlobals::_INPUT_BUFF = R"()";
std::string TesterGlobals::_OUTPUT_BUFF = R"()";
std::string TesterGlobals::_EXPECTED_OUTPUT = R"()";

bool TesterGlobals::print_cls = true;
bool TesterGlobals::print_pause = true;
Color TesterGlobals::index_color = Color::D_PINK;
Color TesterGlobals::changed_color = Color::D_SKYBLUE;


std::string strip(const std::string& str) {
	size_t begin = 0, end = str.size();
	while (true) {
		if (begin >= str.size()) return "";
		if (str[begin] != ' ' && str[begin] != '\n')break;
		begin++;
	}

	while (true) {
		if (str[end - 1] != ' ' && str[end - 1] != '\n') break;
		end--;
	}
	return str.substr(begin, end - begin);
}


#ifdef _WIN32
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void set_cursor_pos(int column, int line) {
	COORD coord; coord.X = column; coord.Y = line;
	if (!SetConsoleCursorPosition(hConsole, coord)) { /*ERROR*/ }
}

void cprint(const char* p_msg, Color p_fg, Color p_bg) {
	#define SET_CCOLOR(m_fg, m_bg) SetConsoleTextAttribute(hConsole, (int)m_bg << 4 | (int)m_fg)
	SET_CCOLOR(p_fg, p_bg);
	printf(p_msg);
	SET_CCOLOR(Color::L_WHITE, Color::BLACK);
}

void clear_console() {
	system("cls");
}

#else
void set_cursor_pos(int column, int line) {  // only works in ANSI compatible terminal.
	printf("\033[%d;%dH", column + 1, line + 1);
}

void cprint(const char* p_msg, Color p_fg, Color p_bg) { /* TODO: implement */ }

void clear_console() {
	system("clear");
}
#endif

// DBPRINT IMPLEMENTATIONS ////////////////////////////////////////////////////////////////////////////////


void VecPrinter::dbprint() {
	printf("[");
	for (int i = 0; i < (int)src->size(); i++) {
		if (i) printf((i != r) ? ", " : " ");

		int width_reduction = 0;

		if (i == l) cprint("[", TesterGlobals::index_color), width_reduction++;
		if (i == ind) cprint("#", TesterGlobals::index_color), width_reduction++;
		if (i == r) width_reduction++;

		Color elem_color = Color::L_WHITE;
		int elem = (*src)[i];
		if (i < copy.size()) {
			if (copy[i] != elem) copy[i] = elem, elem_color = TesterGlobals::changed_color;
		} else { // new element inserted.
			copy.push_back(elem);
			elem_color = TesterGlobals::changed_color;
		}
		std::map<int, Color>::iterator it = elem_color_override.find(i);
		if (it != elem_color_override.end()) elem_color = it->second;

		std::string elem_str = std::to_string(elem);
		while (elem_str.size() < elem_width) elem_str = " " + elem_str;
		cprint(elem_str.c_str(), elem_color);

		if (i + 1 == r) cprint("]", TesterGlobals::index_color);
	}
	printf(" ]\n");
}


#endif // TESTER_IMPL