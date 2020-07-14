#pragma once

#include <stdio.h>
#include <time.h>
#include<io.h>
#include <fcntl.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <algorithm>
#include <chrono>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <unordered_map>

#define TEST_RUNS 10
#define print(x) std::cout << (x) << std::endl

#if ALGO_DEBUG
#define RUN(m_func) m_func;
#else
#define RUN(m_func)                                                                          \
do {                                                                                         \
	printf("------------------\nTest\n------------------\n");                                \
	double avg = 0;                                                                          \
	for (int i = 0; i < TEST_RUNS; i++) {                                                    \
		auto start = std::chrono::high_resolution_clock::now();                              \
		m_func;                                                                              \
		auto end = std::chrono::high_resolution_clock::now();                                \
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);  \
		printf("Test %2i time: %lli\n", i, duration.count());                                \
		avg = (avg * i + duration.count()) / (i + 1);                                        \
	}                                                                                        \
	printf("------------------\nAverage time: %f\n------------------\n\n", avg);             \
} while(false)
#endif


template<typename T>
void _vec_push_back(std::vector<T> & vec) {
	return;
}
template<typename T, typename... Targs>
void _vec_push_back(std::vector<T> & vec, T arg1, Targs... args) {
	vec.push_back(arg1);
	_vec_push_back(vec, args...);
}

template <typename T, typename... Targs>
std::vector<T> Vector(Targs... args) {
	std::vector<T> ret;
	_vec_push_back(ret, args...);
	return ret;
}

template<typename T>
inline void printvec(const std::vector<T>& vec) {
	printf("[");
	for (int i = 0; i < vec.size(); i++) {
		if (i != 0) printf(", ");
		printf("%s", std::to_string(vec[i]).c_str());
	}
	printf("]\n");
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
void cprint(const char* p_msg, Color p_fg = Color::D_WHITE, Color p_bg = Color::BLACK);

void sleep(unsigned milliseconds);
void set_cursor_pos(int column=0, int line=0);