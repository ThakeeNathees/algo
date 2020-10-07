
// Headers ////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <cmath>

#include <string>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>

// Macros //////////////////////////////////////////////////////
#ifdef _TESTING
	#define CPP_IMPL
	#include "include.h"
#else
	#define MAIN main
	#define REDIRECT()
#endif

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#if !defined(INT_MIN) && !defined (INT_MAX)
	#define INT_MIN     (-2147483647 - 1)
	#define INT_MAX       2147483647
#endif

typedef std::vector<int> ivec;
typedef std::vector<ivec> ivec2d;
typedef std::string string;
typedef std::vector<string> svec;
typedef long long ll;

// printf/scanf are much faster than stdin/stdout but can't use them for testing with redirect.
#ifdef _TESTING
	#define INPUT_INT(m_name) int m_name; std::cin >> m_name
	#define PRINT_INT(m_name) PRINT(m_name)
	#define PRINTLN_STR(m_name) PRINT(m_name)
	#define LN std::cout << endl
#else
	#define INPUT_INT(m_name) int m_name; scanf("%i", &m_name)
	#define PRINT_INT(m_name) printf("%i", m_name)
	#define PRINTLN_STR(m_name) printf("%s\n", m_name)
	#define LN printf("\n")
#endif

#define INPUT_LINE(m_name) std::string m_name; std::getline(std::cin, m_name)
#define INPUT_IARR(m_arr, m_size) std::vector<int> m_arr; for (int _i = 0; _i < m_size; _i++) { INPUT(int, inp); m_arr.push_back(inp); }
#define EOL() do { std::string _line; std::getline(std::cin, _line); } while (false)
#define ARR_ERASE(m_arr, m_elem) m_arr.erase(std::find(m_arr.begin(), m_arr.end(), m_elem));
#define ARR_SORT(m_arr) std::sort(m_arr.begin(), m_arr.end())
#define PRINT(m_what)  std::cout << (m_what)
#define PRINTLN(m_what) std::cout << (m_what) << std::endl
#define FOR(m_i, m_n) for (int m_i = 0; m_i < m_n; m_i++)
#define FORL(m_i, m_begin, m_end) for (int m_i = m_begin; m_i < m_end; m_i++)

#define KICK_START() INPUT(int, T); for (int t = 1; t <= T; t++) { std::cout << "Case #" << t << ": " << KickStart() << std::endl; }
int KickStart() { return {}; }

// Main ///////////////////////////////////////////////////////
int MAIN() {
	REDIRECT();
	//KICK_START();

	return 0;
}

// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {

	// CHECK_EQ(, );
	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

