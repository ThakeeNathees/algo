
// Headers and Macros ////////////////////////////////////////
#ifdef _TESTING
	#define CPP_IMPL
	#include "include.h"
#else
	#include <bits/stdc++.h>
	#define MAIN main
	#define REDIRECT()
#endif

#define input(m_type, m_name) m_type m_name; std::cin >> m_name
#define print(m_what)  std::cout << (m_what)
#define println(m_what) std::cout << (m_what) << std::endl
#define FOR(i, N) for (int i = 0; i < N; i++)

typedef std::vector<int> ivec;
typedef std::vector<ivec> ivec2d;
typedef std::string string;
typedef long long ll;

// Main ///////////////////////////////////////////////////////

struct SwitchIndex {
	int _ind = 0;
	inline int ind() const { return _ind; }
	inline int incr() { int ret = _ind; _ind = (_ind + 1) % 2; return ret; }
	inline int prev() const { return (_ind + 1) % 2; }
};


int MAIN() {
	REDIRECT();
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

	input(int, N);
	ivec2d arr(2, ivec());
	SwitchIndex si;
	FOR(n, 2*N -1) {
		input(int, a);
		arr[si.ind()].push_back(a);
	}

	while (arr[si.ind()].size() > 1) {
		si.incr(); arr[si.ind()].clear();

		for (int i = 0; i < arr[si.prev()].size() - 2; i++) {

			int b1 = arr[si.prev()][i], b2 = arr[si.prev()][i + 1], b3 = arr[si.prev()][i + 2];
			int m;

			if ((b1 < b2 && b2 < b3) || (b3 < b2 && b2 < b1)) m = b2;
			else if ((b2 < b1 && b1 < b3) || (b3 < b1 && b1 < b2)) m = b1;
			else m = b3;

			arr[si.ind()].push_back(m);
		}
	}
	println(arr[si.ind()][0]);


	return 0;
}


// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {
	TEST_MAIN(R"(4
1 6 3 7 4 5 2)", R"(4)");


	// CHECK_EQ(Solution(), );
	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

