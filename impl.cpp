
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
bool Globals::draw_pause = true;
Color Globals::index_color = Color::D_PINK;
Color Globals::changed_color = Color::D_SKYBLUE;


Drawable::_DrawState::_DrawState(const char* str) {
	strliteral = str;
	drawable = new StringDraw("strliteral", &strliteral); // memory leak is acceptable for debugging.
}

void IvecDraw::draw(int l, int r, int ind) {

	printf("%s = [", name);
	for (int i = 0; i < parr->size(); i++) {
		if (i && i != r) printf(",");

		if (i == l) {
			if (r == -1) cprint("#", Globals::index_color);
			else cprint("[", Globals::index_color);
		}
		if (i == ind) cprint("#", Globals::index_color);

		else if (i) printf(" "); // space after the above comma.
		
		Color element_color = Color::L_WHITE;
		if (copy.size() > i) {
			if (copy[i] != (*parr)[i]) {
				copy[i] = (*parr)[i];
				element_color = Globals::changed_color;
			}
		} else {
			copy.push_back((*parr)[i]);
			element_color = Globals::changed_color;
		}
		auto it = color_override.find(i);
		if (it != color_override.end()) element_color = it->second;
		cprint(std::to_string((*parr)[i]).c_str(), element_color);

		if (i + 1 == r) cprint("]", Globals::index_color);
	}
	printf(" ]\n");
}

void Ivec2dDraw::draw(int x, int y, int z) {

	int x1, y1, x2, y2;
	if (range) {
		x1 = x / (*pvec)[0].size(); y1 = x % (*pvec)[0].size();
		x2 = (y - 1) / (*pvec)[0].size(); y2 = (y - 1) % (*pvec)[0].size();
	} else {
		x1 = x2 = x;
		y1 = y2 = y;
	}

	printf("%s =\n", name);
	for (int i = 0; i < (*pvec).size(); i++) {

		if (copy.size() == i) { copy.push_back(ivec()); }
		for (int j = 0; j < (*pvec)[i].size(); j++) {

			if (j && ((i != x1 || j-1 != y1) && (i != x2 || j - 1 != y2))) printf(","); // ?

			if ((z/(*pvec)[0].size() == i) && (z % (*pvec)[0].size() == j))
				cprint((j == 0) ? "#" : " #", Globals::index_color);
			else if (i == x1 && j == y1) cprint((j == 0) ? "[" : " [", Globals::index_color);
			else if (j) printf(" ");

			int _int_wide = (i == x1 && j == y1) ? (int_wide - 1) : int_wide;
			if (copy[i].size() == j) {
				char buff[10] = { 0 };
				sprintf(buff, "%*i", _int_wide, (*pvec)[i][j]);
				if (no_zero && (*pvec)[i][j] == 0) { for (int i = 0; i < 10; i++) if (buff[i] == '0') { buff[i] = ' '; break; } }
				cprint(buff, Globals::changed_color);
				copy[i].push_back((*pvec)[i][j]);
			} else {
				if (copy[i][j] != (*pvec)[i][j]) {
					copy[i][j] = (*pvec)[i][j];
					char buff[10] = { 0 };
					sprintf(buff, "%*i", _int_wide, (*pvec)[i][j]);
					if (no_zero && (*pvec)[i][j] == 0) { for (int i = 0; i < 10; i++) if (buff[i] == '0') { buff[i] = ' '; break; } }
					cprint(buff, Globals::changed_color);
					copy[i].push_back((*pvec)[i][j]);
				} else {
					if (no_zero && (*pvec)[i][j] == 0) {
						printf("%*c", _int_wide, ' ');
					} else {
						printf("%*i", _int_wide, (*pvec)[i][j]);
					}
				}
			}

			if (i == x2 && j == y2) cprint("]", Globals::index_color);
			
		} printf("\n");
	}
}

void IntDraw::draw() {
	printf("%s = ", name);
	if (copy != *i){
		cprint(std::to_string(*i).c_str(), Globals::changed_color);
		copy = *i;
	} else {
		printf("%i", copy);
	} printf("\n");
}

void StringDraw::draw(int l, int r) {

	if (l != -1 && r == -1) r = l + 1;

	printf("%s = ", name);
	for (int i = 0; i <= (int)str->size(); i++) {
		char c = (*str)[i];

		if (i == l) cprint("[", Globals::index_color);
		if (i >= copy.size()) {
			cprint(string(1, c).c_str(), Globals::changed_color);
			copy += c;
		} else {
			if (copy[i] != c) {
				cprint(string(1, c).c_str(), Globals::changed_color);
				copy[i] = c;
			} else {
				printf("%c", c);
			}
		}
		if (i + 1 == r) cprint("]", Globals::index_color);
	} printf("\n");
}

void ArrTreeDraw::_recursive_draw(int ind, string indent, int db_ind) {
	bool is_right = ind & 1, is_root = ind == 1; // root index is 1 not 0.
	printf("%s", indent.c_str());

	if (!is_root) {
		if (is_right) {
			printf(" |__");
			indent += "    ";
		} else {
			printf(" |--");
			indent += " |  ";
		}
	}

	if (ind < tree->size()) {
		printf(" "); // negative numbers have a minus.
		if (ind == db_ind) cprint("[", Globals::index_color);
		if (copy.size() <= ind) {
			copy.resize(tree->size());
			copy[ind] = (*tree)[ind];
			cprint(std::to_string((*tree)[ind]).c_str(), Globals::changed_color);
		} else if (copy[ind] != (*tree)[ind]) {
			copy[ind] = (*tree)[ind];
			cprint(std::to_string((*tree)[ind]).c_str(), Globals::changed_color);
		} else printf("%i", (*tree)[ind]);
		if (ind == db_ind) cprint("]", Globals::index_color);
		printf("\n");

	}
	else cprint("null\n", Color::L_RED);


	if (ind < tree->size() && (((ind * 2) < tree->size()) || ((ind * 2 + 1) < tree->size()))) {
		_recursive_draw(2 * ind, indent, db_ind);
		_recursive_draw(2 * ind + 1, indent, db_ind);
	}

	if (is_right && (ind > tree->size() || ((ind * 2 > tree->size()) && (ind * 2 + 1 > tree->size()))))
		printf("%s\n", indent.c_str());
}

///////////////////////////////////////////////////////////////