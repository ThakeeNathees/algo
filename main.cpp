
// Headers ////////////////////////////////////////////////////
#include <algorithm>
#include <iostream>
#include <vector>

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

#define INPUT(m_type, m_name) m_type m_name; std::cin >> m_name
#define INPUT_LINE(m_name) std::string m_name; std::getline(std::cin, m_name)
#define INPUT_IARR(m_arr, m_size) std::vector<int> m_arr; for (int _i = 0; _i < m_size; _i++) { INPUT(int, inp); m_arr.push_back(inp); }
#define EOL() do { std::string _line; std::getline(std::cin, _line); } while (false)
#define ERASE_ARR(m_arr, m_elem) m_arr.erase(std::find(m_arr.begin(), m_arr.end(), m_elem));
#define PRINT(m_what)  std::cout << (m_what)
#define PRINTLN(m_what) std::cout << (m_what) << std::endl


// Main ///////////////////////////////////////////////////////
int MAIN() {
	REDIRECT();

	return 0;
}


// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {

	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

