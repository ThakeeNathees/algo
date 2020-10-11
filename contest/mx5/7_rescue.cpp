
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

inline int Sn(int begin, int end) {
	begin++; end++;
	return ((end) * (end + 1) / 2) - (begin) * (begin + 1) / 2;
}

int MAIN() {
	REDIRECT();
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

	int N, H, M;
	std::cin >> N >> H >> M;

	std::vector<std::pair<int, int>> ans; int heat = 1;
	ans.push_back({1, 1});

	for (int i = 2; i <= N; i++) {
		auto current = ans[ans.size() - 1];
		if (heat + i > H || (current.second - current.first + 1) + 1 > M) {
			ans.push_back({i, i});
			heat = i; continue;
		}

		heat += i;
		ans[ans.size() - 1].second++;
	}

	println(ans.size());
	for (auto p : ans) {
		for (int i = p.first; i <= p.second; i++) {
			if (i != p.first) print(" ");
			print(i);
		} println("");
	}

	return 0;
}


// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {
	TEST_MAIN(R"(10  12  3)", R"(7
1 2 3
4 5
6
7
8
9
10)");

	TEST_MAIN(R"(20 40 5)", R"(7
1 2 3 4 5
6 7 8 9 10
11 12 13
14 15
16 17
18 19
20)");

	// CHECK_EQ(Solution(), );
	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

