
#include "include.h"

#ifdef _WIN32
	#define NOMINMAX
	#include <windows.h>
#else
	#include <unistd.h>
#endif

std::string strip(const std::string& str) {
	size_t begin = 0, end = str.size();

	while (true) {
		if (begin >= str.size()) return "";
		if (str[begin] != ' ' && str[begin] != '\n') {
			break;
		}
		begin++;
	}

	while (true) {
		if (str[end - 1] != ' ' && str[end - 1] != '\n') {
			break;
		}
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

void clear_console() {
	system("clear");
}
#endif

// dbprint classes ////////////////////////////////////////////
void IvecDraw::draw(int l, int r) {

	printf("%s = [", name);
	for (int i = 0; i < parr->size(); i++) {
		if (i && i != r) printf(",");

		if (i == l) {
			if (r == -1) cprint("#", Color::D_PINK);
			else cprint("[", Color::D_PINK);
		}
		else if (i) printf(" "); // space after the above comma.
		
		if (copy.size() > i) {
			if (copy[i] != (*parr)[i]) {
				copy[i] = (*parr)[i];
				cprint(std::to_string((*parr)[i]).c_str(), Color::D_GREEN);
			} else {
				printf("%i", (*parr)[i]);
			}
		} else {
			copy.push_back((*parr)[i]);
			cprint(std::to_string((*parr)[i]).c_str(), Color::D_GREEN);
		}

		if (i + 1 == r) cprint("]", Color::D_PINK);
	}
	printf(" ]\n");
}

void Ivec2dDraw::draw(int x, int y) {

	printf("%s =\n", name);
	for (int i = 0; i < (*pvec).size(); i++) {

		if (copy.size() == i) { copy.push_back(ivec()); }
		for (int j = 0; j < (*pvec)[i].size(); j++) {

			if (j && (i != x || j-1 != y)) printf(",");
			if (i == x && j == y) cprint((j == 0) ? "[" : " [", Color::D_PINK);
			else if (j) printf(" ");

			int _int_wide = (i == x && j == y) ? (int_wide-1) : int_wide;
			if (copy[i].size() == j) {
				char buff[10] = { 0 };
				sprintf(buff, "%*i", _int_wide, (*pvec)[i][j]);
				if (no_zero && (*pvec)[i][j] == 0) { for (int i = 0; i < 10; i++) if (buff[i] == '0') { buff[i] = ' '; break; } }
				cprint(buff, Color::D_GREEN);
				copy[i].push_back((*pvec)[i][j]);
			} else {
				if (copy[i][j] != (*pvec)[i][j]) {
					copy[i][j] = (*pvec)[i][j];
					char buff[10] = { 0 };
					sprintf(buff, "%*i", _int_wide, (*pvec)[i][j]);
					if (no_zero && (*pvec)[i][j] == 0) { for (int i = 0; i < 10; i++) if (buff[i] == '0') { buff[i] = ' '; break; } }
					cprint(buff, Color::D_GREEN);
					copy[i].push_back((*pvec)[i][j]);
				} else {
					if (no_zero && (*pvec)[i][j] == 0) {
						printf("%*c", _int_wide, ' ');
					} else {
						printf("%*i", _int_wide, (*pvec)[i][j]);
					}
				}
			}

			if (i == x && j == y) cprint("]", Color::D_PINK);
			
		} printf("\n");
	}
}

void IntDraw::draw() {
	printf("%s = ", name);
	if (copy != *i){
		cprint(std::to_string(*i).c_str(), Color::D_GREEN);
		copy = *i;
	} else {
		printf("%i", copy);
	} printf("\n");
}

///////////////////////////////////////////////////////////////