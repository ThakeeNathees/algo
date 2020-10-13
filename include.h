#pragma once

// HEADERS /////////////////////////////////////////////////////

#include "bits/stdc++.h"
#include "dbprint.h"

// MACROS //////////////////////////////////////////////////

#define MAIN _main
#define TEST main

#define STR(x) #x
#define TOSTRING(x) STR(x)

#define CHECK(m_exp)                                \
do {                                                \
	printf("TEST (line:" TOSTRING(__LINE__) "): "); \
	if (!(m_exp)) {                                 \
 	   cprint("FAILURE\n", Color::L_RED);           \
	} else {                                        \
		cprint("SUCCESS\n", Color::L_GREEN);        \
	}                                               \
} while (false)

#define CHECK_EQ(m_result, m_expected)                               \
do {                                                                 \
	printf("TEST (line:" TOSTRING(__LINE__) "): ");                  \
	if (m_result != m_expected) {                                    \
		cprint("FAILURE\n", Color::L_RED);                           \
		printf("\tEXPECTED : %s\n", _to_string(m_expected).c_str()); \
		printf("\tRESULT   : %s\n", _to_string(m_result).c_str());   \
	} else {                                                         \
		cprint("SUCCESS\n", Color::L_GREEN);                         \
	}                                                                \
}  while (false)


#ifdef CPP_IMPL
// Yes it's a global variable I know.
std::chrono::steady_clock::time_point g_t0;
std::chrono::duration<double> g_duration;
int g_timer_line;
// for timeing a piece of code on the
#define TIMER_START() g_timer_line = __LINE__; g_t0 = std::chrono::steady_clock::now()
#define TIMER_END()                                 \
	printf("TIMER (line:%i): ", g_timer_line);      \
	g_duration = std::chrono::steady_clock::now() - g_t0; cprint(_to_string(g_duration.count() * 1000).append(" ms\n").c_str(), Color::L_SKYBLUE)
#endif

#ifdef CPP_IMPL
// Yes it's a global variable I know.
std::string _INPUT_BUFF = R"()";
std::string _OUTPUT_BUFF = R"()";
std::string _EXPECTED_OUTPUT = R"()";

#define REDIRECT()                                   \
class Redirect {									 \
	std::istringstream isstream;					 \
	std::ostringstream osstream;					 \
	std::streambuf* istream_buf;					 \
	std::streambuf* ostream_buf;					 \
public:												 \
	Redirect() {									 \
		istream_buf = std::cin.rdbuf();				 \
		isstream = std::istringstream(_INPUT_BUFF);	 \
		std::cin.rdbuf(isstream.rdbuf());			 \
		ostream_buf = std::cout.rdbuf();			 \
		osstream = std::ostringstream(_OUTPUT_BUFF); \
		std::cout.rdbuf(osstream.rdbuf());			 \
	}												 \
	~Redirect() {									 \
		_OUTPUT_BUFF = strip(osstream.str());		 \
		std::cin.rdbuf(istream_buf);				 \
		std::cout.rdbuf(ostream_buf);				 \
	}												 \
};													 \
Redirect redirect

#define RUN_MAIN(m_input_buff)                       \
	_INPUT_BUFF = strip(m_input_buff);               \
	_OUTPUT_BUFF = "";                               \
	MAIN()

#define TEST_MAIN(m_input_buff, m_output_buff)                   \
	_EXPECTED_OUTPUT = strip(m_output_buff);                     \
	RUN_MAIN(m_input_buff);                                      \
	printf("LINE [" TOSTRING(__LINE__) "]: ");                   \
	if (_OUTPUT_BUFF != _EXPECTED_OUTPUT ) {                     \
		cprint("FAILURE\n", Color::L_RED);                       \
		cprint("\tEXPECTED : ", Color::L_YELLOW); printf("%s\n", _EXPECTED_OUTPUT .c_str());  \
		cprint("\tRESULT   : ", Color::L_YELLOW); printf("%s\n", _OUTPUT_BUFF.c_str());       \
	} else {                                                     \
		cprint("SUCCESS\n", Color::L_GREEN);                     \
	}

#endif // CPP_IMPL

// DECLARATIONS //////////////////////////////////////////////////

std::string strip(const std::string& str);

template <typename T>
std::string _to_string(T value) {
	if constexpr (std::is_arithmetic<T>::value) {
		return std::to_string(value);
	} else if constexpr (std::is_same<T, std::string>::value || std::is_same<T, const std::string&>::value) {
		return value;
	} else if constexpr (
		std::is_same<T, std::vector<int>>::value ||
		std::is_same<T, std::vector<long>>::value ||
		std::is_same<T, std::vector<float>>::value ||
		std::is_same<T, std::vector<double>>::value
		) {
		std::string ret = "[ ";
		for (size_t i = 0; i < value.size(); i++) {
			if (i != 0) ret += ", ";
			ret += std::to_string(value[i]);
		}
		ret += " ]";
		return ret;
	} else if constexpr (std::is_same<T, const char*>::value) {
		return value;
	}
}


