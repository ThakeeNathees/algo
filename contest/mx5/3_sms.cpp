
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
int MAIN() {
	REDIRECT();
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

	input(string, s1); input(string, s2);

	ivec2d char_pos(27, ivec());
	for (int i = 0; i < s2.size(); i++) {
		if (s2[i] == '[') continue;
		char_pos[s2[i] - 'A'].push_back(i);
	}

	ll ans = 0;
	FOR(i, s1.size()) {
		if (s1[i] == '[') continue;
		//int ind = s1[i] == '[' ? 26 : s1[i] - 'A';
		int ind = s1[i] - 'A';
		if (i < s2.size() - 1) {
			for (int cind : char_pos[ind]) {
				if (cind > i) break;
				ans++;
			}
		} else if (i + s2.size() > s1.size()) {
			int lbi = s2.size() - (s1.size() - i);
			for (int cind : char_pos[ind]) {
				if (cind >= lbi) ans++;
			}
		} else {
			ans += char_pos[ind].size();
		}
	}
	println(ans);

	return 0;
}


// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {
	TEST_MAIN(R"(LYOUMELOVE
LOVE)", R"(7)");


	TEST_MAIN(R"(A[[A[[
A[)", R"(2)");

	TEST_MAIN(R"(AAA
AA)", R"(4)");

	// CHECK_EQ(Solution(), );
	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

