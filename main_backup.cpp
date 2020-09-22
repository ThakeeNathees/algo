
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

#define PRINT(m_what)  std::cout << (m_what)
#define PRINTLN(m_what) std::cout << (m_what) << std::endl

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

}
#endif // _TESTING
