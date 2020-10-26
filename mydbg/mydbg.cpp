
#include "core.h"

#ifdef _WIN32
	#define NOMINMAX
	#include <windows.h>
#else
	#include <unistd.h>
#endif

int TesterGlobals::timer_line;
std::chrono::steady_clock::time_point TesterGlobals::timer_t0;
std::chrono::duration<double> TesterGlobals::timer_duration;

std::string TesterGlobals::_INPUT_BUFF = R"()";
std::string TesterGlobals::_OUTPUT_BUFF = R"()";
std::string TesterGlobals::_EXPECTED_OUTPUT = R"()";

bool TesterGlobals::print_cls = true;
bool TesterGlobals::print_pause = true;
Color TesterGlobals::index_color = Color::D_PINK;
Color TesterGlobals::changed_color = Color::D_SKYBLUE;

std::vector<Printable*> TesterGlobals::printables;

std::string strip(const std::string& str) {
	size_t begin = 0, end = str.size();
	while (true) {
		if (begin >= str.size()) return "";
		if (str[begin] != ' ' && str[begin] != '\n') break;
		begin++;
	}

	while (true) {
		if (str[end - 1] != ' ' && str[end - 1] != '\n') break;
		end--;
	}
	return str.substr(begin, end - begin);
}


#ifdef _WIN32
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void set_cursor_pos(int column, int line) {
	COORD coord; coord.X = column; coord.Y = line;
	if (!SetConsoleCursorPosition(hConsole, coord)) { /*ERROR*/ }
}

void cprint(const char* p_msg, Color p_fg, Color p_bg) {
	#define SET_CCOLOR(m_fg, m_bg) SetConsoleTextAttribute(hConsole, (int)m_bg << 4 | (int)m_fg)
	SET_CCOLOR(p_fg, p_bg);
	printf(p_msg);
	SET_CCOLOR(Color::L_WHITE, Color::BLACK);
}

void clear_console() {
	system("cls");
}

#else
void set_cursor_pos(int column, int line) {  // only works in ANSI compatible terminal.
	printf("\033[%d;%dH", column + 1, line + 1);
}

void cprint(const char* p_msg, Color p_fg, Color p_bg) { /* TODO: implement */ }

void clear_console() {
	system("clear");
}
#endif

// DBPRINT IMPLEMENTATIONS ////////////////////////////////////////////////////////////////////////////////


