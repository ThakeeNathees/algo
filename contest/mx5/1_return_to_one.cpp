
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

	input(int, N);
	FOR(n, N) {
		input(int, kapila); input(int, kalpa);
		if (kapila == kalpa) {
			println("-");
		} else {
			while (kapila != 1 && kalpa != 1) {

				if (kapila == kalpa) break;

				if (kapila % 2) {
					kapila = kapila * 3 + 1;
				} else {
					kapila /= 2;
				}

				if (kalpa % 2) {
					kalpa = kalpa * 3 + 1;
				} else {
					kalpa /= 2;
				}
			}

			if (kapila == kalpa) {
				println("-");
			} else if (kapila == 1) {
				println("Kapila");
			} else {
				println("Kalpa");
			}
		}
	}


	return 0;
}


// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {
	TEST_MAIN(R"(2
256 250 
457 512)", R"(Kapila
Kalpa)");

	TEST_MAIN(R"(3
13 9
25 6
9 9)", R"(Kapila
Kalpa
-)");

	// CHECK_EQ(Solution(), );
	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

