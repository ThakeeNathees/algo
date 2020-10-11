
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

	input(int, N); std::cin >> N;
	int n = N;
	int arr[10] = { 0 };
	while (n) {
		arr[n % 10]++;
		n /= 10;
	}

	for (int i = 9; i > 3; i--) {
		if (arr[i] > 0) {

			bool done = false;
			while (arr[i] > 0) {
				
				switch (i) {
					case 9: {
						if (arr[2] >= 2) {
							arr[2] -= 2;
							arr[3] += 2;
							arr[i]--; arr[i - 1]++;
						} else done = true;
					} break;
					case 8: {
						if (arr[3] > 0) {
							arr[3]--;
							arr[4]++;
							arr[2]++;
							arr[i]--; arr[i - 1]++;
						} else done = true;
					} break;
					case 6: {
						arr[5]++;
						arr[3]++;
						arr[i]--;
					} break;
					case 4: {
						arr[i]--; arr[i - 1]++;
						arr[2] += 2;
					} break;

					default: {
						done = true;
					}
				}

				if (done) break;
			}
		}
	}

	int ans = 0;
	for (int i = 9; i >= 2; i--) {
		while (arr[i]--) {
			print(i);
		}
	} println("");

	return 0;
}

// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {
	TEST_MAIN(R"(4
1256)", R"(5532)");

	TEST_MAIN(R"(3
564)", R"(553322)");

	TEST_MAIN(R"(8
22334455)", R"(553333222222)");

	TEST_MAIN(R"(8
98546799)", R"(77777553333333322222222)");

	// CHECK_EQ(Solution(), );
	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

