
// Headers ///////////////
#include <algorithm>
#include <iostream>
#include <vector>
// #include <stdio.h> // don't use scanf(), printf() <- can't debug.

//#undef _TESTING

// Macros /////////////////
#ifdef _TESTING
	#define CPP_IMPL
	#include "include.h"
#else
	#define MAIN main
	#define __SET_IOBUFF__ 
	#define __RESET_IOBUFF__
	#define REDIRECT()
#endif

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// eat temp chars from input buffer ex: 1,2,3,4
#define INPUT_EAT()        \
	do { 				   \
		char _tmp;		   \
		std::cin >> _tmp;  \
	} while (false)

#define INPUT_GET(m_type, m_name) \
	m_type m_name;				  \
	std::cin >> m_name

#define PRINT(m_what)  std::cout << (m_what)
#define PRINTL(m_what) std::cout << (m_what) << std::endl

// Main /////////////////
int MAIN() {
	REDIRECT();

	// code();

	return 0;
}


// Tests /////////////////
#ifdef _TESTING

int TEST() {
	// TEST_MAIN(R"()", R"()");
	TEST_MAIN(R"()", R"()");
}
#endif

