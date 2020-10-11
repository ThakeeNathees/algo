#pragma once

#define DBG_IVEC(name, arr) IvecDraw name = IvecDraw(#name, &(arr))
#define DBG_IVEC2D(name, vec) Ivec2dDraw name = Ivec2dDraw(#name, &(vec))
#define DBG_INT(name, i) IntDraw name = IntDraw(#name, &i)

typedef std::vector<int> ivec;
typedef std::vector<ivec> ivec2d;
typedef std::string string;
typedef long long ll;

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

// draw subarray with int l, r;
class IvecDraw {
public:
	const char* name;
	ivec* parr; ivec copy;

	IvecDraw(const char* name, ivec* parr) : name(name), parr(parr), copy(*parr) {}
	void draw(int l = -1, int r = -1);
};

class Ivec2dDraw {
public:
	const char* name; int int_wide = 3;
	ivec2d* pvec; ivec2d copy;
	Ivec2dDraw(const char* name, ivec2d* pvec) : name(name), pvec(pvec), copy(*pvec) {}
	void draw(int ind_x = -1, int ind_y = -1);
};

class IntDraw {
public:
	const char* name;
	int* i; int copy;
	IntDraw(const char* name, int* i) : name(name), i(i), copy(*i) {}
	void draw();
};

void clear_console();
void set_cursor_pos(int column, int line);
void cprint(const char* p_msg, Color p_fg, Color p_bg = Color::BLACK);