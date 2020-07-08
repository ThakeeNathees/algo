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

#include <chrono>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

class Tester {
public:
	Tester() {}

	void run_tests(const std::string& p_name, int tests = 1) {
		printf("------------------\nTest: %s\n------------------\n", p_name.c_str());
		double avg = 0;
		for (int i = 0; i < tests; i++) {
			auto start = std::chrono::high_resolution_clock::now();
			run();
			auto end = std::chrono::high_resolution_clock::now();		
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			printf("Test %2i time: %lli\n", i, duration.count());
			avg = (avg * i + duration.count()) / (i + 1);
		}
		printf("------------------\nAverage time: %f\n------------------\n\n", avg);
	}

	virtual void run() = 0;

};

#define TIMER(m_name, m_func)                                                           \
do{                                                                                     \
	auto start = std::chrono::high_resolution_clock::now();                             \
	m_func;                                                                             \
	auto end = std::chrono::high_resolution_clock::now();                               \
                                                                                        \
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); \
	std::cout << m_name << " | druation : " << duration.count() << std::endl;           \
} while(false)

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
void set_cursor_pos(int column, int line);