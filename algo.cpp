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
#else
void set_cursor_pos(int column, int line) {  // only works in ANSI compatible terminal.
    printf("\033[%d;%dH", column + 1, line + 1);
}

#endif

#ifdef _WIN32
#define SET_CCOLOR(m_fg, m_bg) SetConsoleTextAttribute(hConsole, (int)m_bg << 4 | (int)m_fg)
void cprint(const char* p_msg, Color p_fg, Color p_bg) {
    SET_CCOLOR(p_fg, p_bg);
    printf(p_msg);
    SET_CCOLOR(Color::D_WHITE, Color::BLACK);
}
#else
enum ANSI_Codes{
    FG_OFFSET = 0, 
    BG_OFFSET = 10, // fg, bg offset = 10.

    FMT_DEFAULT = 0,
    FMT_BOLD = 1,
    FMT_DIM = 2,
    FMT_UNDERLINED = 3,
    FMT_BLINK = 5,
    FMT_REVERSE = 7,
    FMT_HIDDEN = 8,

    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    WHITE = 37,
    GRAY = 90,
    BRIGHT_RED = 91,
    BRIGHT_GREEN = 92,
    BRIGHT_YELLOW = 93,
    BRIGHT_BLUE = 94,
    BRIGHT_MEGENTA = 95,
    CYAN = 96,
    BRIGHT_WHITE = 97,
    DEFAULT = 39,
    
};
void cprint(const char* p_msg, Color p_fg, Color p_bg) {
#define MAP_COLOR(m_target, m_offset)                                                    \
    switch (p_##m_target) {                                                              \
        case Color::BLACK:     m_target = ANSI_Codes::BLACK + m_offset;          break;  \
        case Color::L_BLUE:    m_target = ANSI_Codes::BLUE + m_offset;           break;  \
        case Color::L_GREEN:   m_target = ANSI_Codes::GREEN + m_offset;          break;  \
        case Color::L_SKYBLUE: m_target = ANSI_Codes::CYAN + m_offset;           break;  \
        case Color::L_RED:     m_target = ANSI_Codes::RED + m_offset;            break;  \
        case Color::L_PINK:    m_target = ANSI_Codes::MAGENTA + m_offset;        break;  \
        case Color::L_YELLOW:  m_target = ANSI_Codes::YELLOW + m_offset;         break;  \
        case Color::L_WHITE:   m_target = ANSI_Codes::WHITE + m_offset;          break;  \
        case Color::L_GRAY:    m_target = ANSI_Codes::GRAY + m_offset;           break;  \
        case Color::D_BLUE:    m_target = ANSI_Codes::BRIGHT_BLUE + m_offset;    break;  \
        case Color::D_GREEN:   m_target = ANSI_Codes::BRIGHT_GREEN + m_offset;   break;  \
        case Color::D_SKYBLUE: m_target = ANSI_Codes::CYAN + m_offset;           break;  \
        case Color::D_RED:     m_target = ANSI_Codes::BRIGHT_RED + m_offset;     break;  \
        case Color::D_PINK:    m_target = ANSI_Codes::BRIGHT_MEGENTA + m_offset; break;  \
        case Color::D_YELLOW:  m_target = ANSI_Codes::BRIGHT_YELLOW + m_offset;  break;  \
        case Color::D_WHITE:   m_target = ANSI_Codes::BRIGHT_WHITE + m_offset;   break;  \
    }
    int fg = ANSI_Codes::WHITE + ANSI_Codes::FG_OFFSET;
    int bg = ANSI_Codes::BLACK + ANSI_Codes::BG_OFFSET;
    MAP_COLOR(fg, ANSI_Codes::FG_OFFSET);
    MAP_COLOR(bg, ANSI_Codes::BG_OFFSET);
    fprintf(stdout, "\033[%i;%i;%im%s\033[%im", ANSI_Codes::FMT_DEFAULT, fg, bg, p_msg, ANSI_Codes::FMT_DEFAULT);
}
#endif

#ifdef _WIN32
void sleep(unsigned milliseconds) { Sleep(milliseconds); }
#else
void sleep(unsigned milliseconds) { usleep(milliseconds * 1000); /* takes microseconds */ }
#endif