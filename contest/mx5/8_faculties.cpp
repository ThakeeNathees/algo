
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

#define MOD ((int)(1e9 + 7))
#define MOD_ADD(a, b, mod) ((((a) % (mod)) + ((b) % (mod))) % (mod))
#define MOD_MUL(a, b, mod) ((((a) % (mod)) * ((b) % (mod))) % (mod))

// Main ///////////////////////////////////////////////////////
int MAIN() {
	REDIRECT();
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

	input(int, N); N--;
	ll Nf = 1;
	for (int i = 1; i <= N; i++) {
		Nf = MOD_MUL(Nf, i, MOD);
	}

	ll Rf = 1;
	for (int i = 2; (N - i) / 2 >= 1; i++) {
		ll tmp = pow((N - i) / 2, 2);
		Rf = MOD_MUL(Rf, tmp, MOD);
	}

	Rf = MOD_MUL(Rf, N-1, MOD);

	int ans = MOD_MUL(Rf, N - 1, MOD);

	println(Nf - Rf);

	return 0;
}


// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {
	TEST_MAIN(R"(4)", R"(16)");


	// CHECK_EQ(Solution(), );
	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

