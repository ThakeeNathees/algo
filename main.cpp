
// include debugging and assertion functions.
#ifdef _VS_DBG
#define CPP_IMPL
#include "include.h"
#endif

#ifdef _VS_DBG
#define MAIN _main

// Yes it's a global variable and I know.
std::string _INPUT_BUFF = R"()";
std::string _OUTPUT_BUFF = R"()";

#define __SET_IOBUFF__                               \
	std::streambuf* istream_buf = std::cin.rdbuf();  \
	std::istringstream isstream(_INPUT_BUFF);        \
	std::cin.rdbuf(isstream.rdbuf());                \
	std::streambuf* ostream_buf = std::cout.rdbuf(); \
	std::ostringstream osstream(_OUTPUT_BUFF);       \
	std::cout.rdbuf(osstream.rdbuf());
#define __RESET_IOBUFF__                             \
	_OUTPUT_BUFF = osstream.str();                   \
	std::cin.rdbuf(istream_buf);                     \
	std::cout.rdbuf(ostream_buf);

#define RUN_MAIN(m_input_buff)                       \
	_INPUT_BUFF = m_input_buff;                      \
	_OUTPUT_BUFF = "";                               \
	MAIN()

#define TEST_MAIN(m_input_buff, m_output_buff)       \
	RUN_MAIN(m_input_buff);                          \
	CHECK(_OUTPUT_BUFF == m_output_buff)

#endif

// START /////////////////////////////////////////////////////////

#ifndef _VS_DBG
#define MAIN main
#define __SET_IOBUFF__ 
#define __RESET_IOBUFF__
#endif

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#include <iostream>
#include <vector>


int MAIN() {
	__SET_IOBUFF__

	int x;
	std::cin >> x;
	std::cout << x * 2;

	__RESET_IOBUFF__
	return 0;
}

// END /////////////////////////////////////////////////////////

#ifdef _VS_DBG
int main() {
	
	TEST_MAIN("1", "2");
	TEST_MAIN("3", "7"); // will fail
	TEST_MAIN("4", "8");
	
}
#endif

