
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

std::set<int> ans;

int atoint(ivec& arr) {
	int ans = 0;
	for (int i : arr) {
		ans *= 10;  ans +=i;
	}
	return ans;
}

void try_path(int _end, int K, string& safe, ivec& ans, bool *done) {
	if (_end == 0) {
		*done = true;
		return;
	}
	for (int i = std::max(_end - K, 0); i < _end; i++) {
		if (safe[i] == '0') {
			ans.push_back(_end - i);
			try_path(i, K, safe, ans, done);
			if (*done) return;
			ans.pop_back();
		}
	}
}

// Main ///////////////////////////////////////////////////////
int MAIN() {
	REDIRECT();
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

	input(int, N); input(int, K);
	input(string, safe);

	if (safe[0] == '1' || safe[N] == '1') {
		println(-1);
		return 0;
	}

	ivec ans; bool done;
	try_path(N, K, safe, ans, &done);
	if (done && ans.size()) {
		for (int i = ans.size() - 1; i >= 0; i--) {
			if (i != ans.size() -1) print(" ");
			print(ans[i]);
		}
		println("");
	} else {
		println(-1);
	}
	return 0;
}


// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {

	ivec arr = {  1, 2, 4, 3, 5 };

	TEST_MAIN(R"(9 3
0001000100)", R"(1 3 2 3)");

	TEST_MAIN(R"(5 4
011110)", R"(-1)");


	TEST_MAIN(R"(6 6
0101010)", R"(6)");

	// CHECK_EQ(Solution(), );
	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

