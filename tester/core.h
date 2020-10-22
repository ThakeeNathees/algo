#ifndef TESTER_H
#define TESTER_H

#include <bits/stdc++.h>

#ifdef INCLUDE_TYPEDEF
	#define input(...) int __VA_ARGS__; read(__VA_ARGS__)
	#define print(m_what)  std::cout << (m_what)
	#define println(m_what) std::cout << (m_what) << std::endl
	#define FOR(i, N) for (size_t i = 0; i < N; i++)
	
	using namespace std;
	template <typename T> using vec = vector<T>;
	typedef long long ll;
	typedef vec<int> ivec; typedef vec<ll> llvec;
	typedef vec<ivec> ivec2d;
#endif

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

#define TEST_MAIN(m_input_buff, m_output_buff)                             \
	TesterGlobals::_EXPECTED_OUTPUT = strip(m_output_buff);                \
	TesterGlobals::_INPUT_BUFF = strip(m_input_buff);                      \
	TesterGlobals::_OUTPUT_BUFF = "";                                      \
	MAIN();                                                                \
	printf("LINE [" STRINGIFY(__LINE__) "]: ");                            \
	if (TesterGlobals::_OUTPUT_BUFF != TesterGlobals::_EXPECTED_OUTPUT ) { \
		cprint("FAILURE\n", Color::L_RED);                                 \
		cprint("\tEXPECTED : ", Color::L_YELLOW); printf("%s\n", TesterGlobals::_EXPECTED_OUTPUT .c_str());  \
		cprint("\tRESULT   : ", Color::L_YELLOW); printf("%s\n", TesterGlobals::_OUTPUT_BUFF.c_str());       \
	} else {                                                               \
		cprint("SUCCESS\n", Color::L_GREEN);                               \
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

template<class T> struct is_vector {
	static bool const value = false;
};
template<class T> struct is_vector<std::vector<T> > {
	static bool const value = true;
};

template<class T> struct is_map {
	static bool const value = false;
};

template<class T1, class T2> struct is_map<std::map<T1, T2> > {
	static bool const value = true;
};

template <typename T>
std::string _to_string(const T& value) {
	if constexpr (std::is_same<T, bool>::value) {
		return value ? "true" : "false";
	} else if constexpr (std::is_arithmetic<T>::value) {
		return std::to_string(value);
	} else if constexpr (std::is_same<T, std::string>::value || std::is_same<T, const std::string&>::value) {
		return value;

	} else if constexpr (std::is_same<T, std::vector<bool>>::value) {
		std::string ret = "[ ";
		for (size_t i = 0; i < value.size(); i++) {
			if (i != 0) ret += ", ";
			ret += (value[i]) ? "true" : "false";
		}
		return ret + " ]";
	} else if constexpr (is_vector<T>::value) {
		std::string ret = "[ ";
		for (size_t i = 0; i < value.size(); i++) {
			if (i != 0) ret += ", ";
			ret += _to_string(value[i]);
		}
		return ret + " ]";

	} else if constexpr (is_map<T>::value) {
		auto it = value.begin();
		std::string ret = "[ ";
		while (it != value.end()) {
			if (it == value.begin()) ret += ", ";
			ret += _to_string(it->first) + " : " + _to_string(it->second);
			it++;
		}
		return ret + " ]";
	} else if constexpr (std::is_same<T, const char*>::value) {
		return value;
	}
	// don't return anything here as it may throw compiler error if any type were missed.
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

#endif // TESTER_H
