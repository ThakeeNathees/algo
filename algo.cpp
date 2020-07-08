#include "algo.h"


#ifdef _WIN32
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

#ifdef _WIN32
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
#endif

#ifdef _WIN32
#define SET_CCOLOR(m_fg, m_bg) SetConsoleTextAttribute(hConsole, (int)m_bg << 4 | (int)m_fg)
void cprint(const char* p_msg, Color p_fg, Color p_bg) {
    SET_CCOLOR(p_fg, p_bg);
    printf(p_msg);
    SET_CCOLOR(Color::D_WHITE, Color::BLACK);
}
#endif

#ifdef _WIN32
void sleep(unsigned milliseconds) { Sleep(milliseconds); }
#else
void sleep(unsigned milliseconds) { usleep(milliseconds * 1000); /* takes microseconds */ }
#endif