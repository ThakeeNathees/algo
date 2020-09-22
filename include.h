#pragma once

// needed for debugging.
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// data_structure : choose wisely.
#if 0
#include <algorithm>
#include <chrono>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#endif

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


template <class Type, class... Types>
void print(const Type& arg, const Types&... args) {
    std::cout << arg;
    ((std::cout << " " << args), ..., (std::cout << std::endl));
}

//#define print(x) std::cout << (x) << std::endl
template <typename T>
void print_vector(const std::vector<T>& x) {
    printf("[ ");
    for (int i = 0; i < x.size(); i++) {
        if (i != 0) printf(", ");
        std::cout << (x[i]);
    }
    printf(" ]\n");
}

#define STR(x) #x
#define TOSTRING(x) STR(x)

#define CHECK(m_exp)                              \
do {                                              \
    printf("LINE [" TOSTRING(__LINE__) "]: ");    \
    if (!(m_exp)) {                               \
        cprint("FAILURE\n", Color::L_RED);        \
    } else {                                      \
        cprint("SUCCESS\n", Color::L_GREEN);      \
    }                                             \
} while (false)

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

#ifdef _WIN32

void set_cursor_pos(int column, int line);
void cprint(const char* p_msg, Color p_fg, Color p_bg);

#ifdef CPP_IMPL
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void set_cursor_pos(int column, int line)
{
    // Create a COORD structure and fill in its members.
    // This specifies the new position of the cursor that we will set.
    COORD coord;
    coord.X = column;
    coord.Y = line;

    // Obtain a handle to the console screen buffer.
    // (You're just using the standard console, so you can use STD_OUTPUT_HANDLE
    // in conjunction with the GetStdHandle() to retrieve the handle.)
    // Note that because it is a standard handle, we don't need to close it.
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Finally, call the SetConsoleCursorPosition function.
    if (!SetConsoleCursorPosition(hConsole, coord)) {
        // Uh-oh! The function call failed, so you need to handle the error.
        // You can call GetLastError() to get a more specific error code.
        // ...
    }
}

#define SET_CCOLOR(m_fg, m_bg) SetConsoleTextAttribute(hConsole, (int)m_bg << 4 | (int)m_fg)
void cprint(const char* p_msg, Color p_fg, Color p_bg = Color::BLACK)
{
    SET_CCOLOR(p_fg, p_bg);
    printf(p_msg);
    SET_CCOLOR(Color::L_WHITE, Color::BLACK);
}

#endif // CPP_IMPL

#else
void set_cursor_pos(int column, int line) {  // only works in ANSI compatible terminal.
    printf("\033[%d;%dH", column + 1, line + 1);
}
#endif



