#ifndef TESTER_H
#define TESTER_H

#include <assert.h>
#include <chrono>
#include <iostream>
#include <functional>
#include <fstream>
#include <iostream>
#include <istream>
#include <limits.h>
#include <sstream>
#include <string>
#include <vector>

// Data structures.
#include <algorithm>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#if __cplusplus >= 201103L
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#endif

#ifdef INCLUDE_TYPEDEF
	
	using namespace std;
	template <typename T> using vec = vector<T>;
	typedef long long ll;
	typedef vec<int> ivec; typedef vec<ll> llvec;
	typedef vec<ivec> ivec2d;
#endif

#define _TESTING
#define MAIN _main
#define TEST main

#define input(...) int __VA_ARGS__; read(__VA_ARGS__)
#define print(m_what)  std::cout << (m_what)
#define println(m_what) std::cout << (m_what) << std::endl
#define FOR(i, N) for (size_t i = 0; i < N; i++)
#define dbreak(cond) if ((cond)) __debugbreak()
#define dbg(exp) printf("%s = %s\n", #exp, _to_string(exp).c_str());

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

class Printable;
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

	static std::vector<Printable*> printables;
};

std::string strip(const std::string& str);
void clear_console();
void set_cursor_pos(int column, int line);
void cprint(const char* p_msg, Color p_fg, Color p_bg = Color::BLACK);


#endif // TESTER_H
