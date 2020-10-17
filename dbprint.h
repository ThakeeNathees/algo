#pragma once

// !!! don't use namespace std here !!!
template <typename T> using vec = std::vector<T>;
typedef std::string string;
typedef long long ll;
typedef vec<int> ivec; typedef vec<ll> llvec;
typedef vec<ivec> ivec2d;

// TODO: implement __line__ in draw function.
#define DBG_IVEC(name, arr) IvecDraw name = IvecDraw(#name, &(arr))
#define DBG_IVEC2D(name, vec) Ivec2dDraw name = Ivec2dDraw(#name, &(vec))
#define DBG_INT(name, i) IntDraw name = IntDraw(#name, &i)
#define DBG_STR(name, str) StringDraw name = StringDraw(#name, &str)
#define DBG_ARRTREE(name, arr) ArrTreeDraw name(#name, &(arr))

// will define a tree printer template function, value type should be int.
#define BTREE_PRINTER(func_name, value, left, right)                                          \
	template<typename _TreeNode_struct_name>                                                  \
	void func_name(_TreeNode_struct_name* node, bool is_right = true, string indent = "",     \
					bool _is_root = true) {                                                   \
                                                                                              \
		printf("%s", indent.c_str());                                                         \
		if (!_is_root) {                                                                      \
			if (is_right) {                                                                   \
				printf(   " |__");                                                            \
				indent += "    ";                                                             \
			} else {                                                                          \
				printf(   " |--");                                                            \
				indent += " |  ";                                                             \
			}                                                                                 \
		}                                                                                     \
		if (node) cprint(std::to_string(node->value).append("\n").c_str(), Color::D_SKYBLUE); \
		else cprint("null\n", Color::L_RED);                                                  \
                                                                                              \
		if (node && (node->left || node->right)) {                                            \
			func_name(node->left, false, indent, false);                                      \
			func_name(node->right, true, indent, false);                                      \
		}                                                                                     \
                                                                                              \
		if (is_right && (!node || (!node->left && !node->right)))                             \
			printf("%s\n", indent.c_str());                                                   \
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

void clear_console();
void set_cursor_pos(int column, int line);
void cprint(const char* p_msg, Color p_fg, Color p_bg = Color::BLACK);

class Globals {
public:
	static bool draw_pause; // will pause after each draw.
	static Color index_color; // 1 2 [3] #4 5  color to indicate index
	static Color changed_color;
};

class Drawable {
public:
	struct _DrawState {
		Drawable* drawable;


		int x = -1, y = -1, z = -1;
		_DrawState(Drawable* drawable, int x = -1, int y = -1, int z = -1) : drawable(drawable), x(x), y(y), z(z) {}
		_DrawState(Drawable& drawable) : drawable(&drawable) {}

		string strliteral;
		_DrawState(const char* str);
	};

	virtual _DrawState operator()(int x = -1, int y = -1, int z = -1) { return {this, x, y, z}; }
	virtual void _draw(int x = -1, int y = -1, int z = -1) = 0;
};

class IvecDraw : public Drawable {
public:
	const char* name;
	ivec* parr; ivec copy;
	std::map<int, Color> color_override; // TODO: refactor everything.

	IvecDraw(const char* name, ivec* parr) : name(name), parr(parr), copy(*parr) {}
	void draw(int l = -1, int r = -1, int i = -1);
	void _draw(int x = -1, int y = -1, int z = -1) override { draw(x, y, z); }
};

class Ivec2dDraw : public Drawable {
public:
	const char* name; int int_wide = 3;
	ivec2d* pvec; ivec2d copy;
	bool no_zero = false, range = false;
	Ivec2dDraw(const char* name, ivec2d* pvec) : name(name), pvec(pvec), copy(*pvec) {}
	void draw(int x = -1, int y = -1, int z = -1);
	void _draw(int x = -1, int y = -1, int z = -1) override { draw(x, y, z); }
};

class IntDraw : public Drawable {
public:
	const char* name;
	int* i; int copy;
	IntDraw(const char* name, int* i) : name(name), i(i), copy(*i) {}
	void draw();
	void _draw(int x = -1, int y = -1, int z = -1) override { draw(); }
};

// TODO fix colors;
class StringDraw : public Drawable {
public:
	const char* name;
	string* str; string copy;
	StringDraw(const char* name, string* str) : name(name), str(str), copy(*str) {}
	void draw(int l = -1, int r= -1);
	void _draw(int x = -1, int y = -1, int z = -1) override { draw(x, y); }
};

// to draw array based tree, root at 1 childs are 2i, 2i+1;
class ArrTreeDraw : public Drawable {
private:
	void _recursive_draw(int ind, string indent = "", int db_ind = -1);
public:
	const char* name;
	ivec* tree; ivec copy;
	ArrTreeDraw(const char* name, ivec* tree) : name(name), tree(tree), copy(*tree) {}
	void draw(int ind = -1) { _recursive_draw(1, "", ind); }
	void _draw(int x = -1, int y = -1, int z = -1) override { draw(x); }
};

template<typename... Args>
void draw(Args... args) {
	clear_console();
	draw_internal(args...);
	if (Globals::draw_pause) getchar();
}

template<typename... Args>
void draw_internal(Drawable::_DrawState drawstate, Args... args) {
	drawstate.drawable->_draw(drawstate.x, drawstate.y, drawstate.z);
	draw_internal(args...);
}

template<typename... Args>
void draw_internal(Drawable::_DrawState drawstate) {
	drawstate.drawable->_draw(drawstate.x, drawstate.y, drawstate.z);
}
