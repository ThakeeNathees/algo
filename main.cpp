
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

#define INPUT(m_type, m_name) m_type m_name; std::cin >> m_name
#define GETLINE(m_name) std::getline(std::cin, m_name)
#define INPUT_IARR(m_arr, m_size) std::vector<int> m_arr; for (int _i = 0; _i < m_size; _i++) { INPUT(int, inp); m_arr.push_back(inp); }

#define PRINT(m_what)  std::cout << (m_what)
#define PRINTLN(m_what) std::cout << (m_what) << std::endl

struct SwitchIndex {
	int _ind = 0;
	inline int ind() const { return _ind; }
	inline int next() const { return (_ind + 1) % 2; }
	inline int prev() const { return next(); }
	inline void incr() { _ind = (_ind + 1) % 2; }
};

// Main ////////////////////////////////////////////////////////
int MAIN() {
	REDIRECT();

	// code();

	return 0;
}


// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {
	// TEST_MAIN(R"()", R"()");

	return 0;
}
#endif // _TESTING

