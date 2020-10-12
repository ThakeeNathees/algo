
// Headers and Macros ////////////////////////////////////////
#ifdef _TESTING
	#define CPP_IMPL
	#include "include.h"
	#define DBPRINT
#else
	#include <bits/stdc++.h>
	#define MAIN main
	#define REDIRECT()
#endif

using namespace std; // Only for CP.
typedef long long ll;
template<typename T> using v = vector<T>;
typedef v<int> vi; typedef v<vi> vi2;
typedef v<ll> vll; typedef v<vll> vll2;

#define input(...) int __VA_ARGS__; read(__VA_ARGS__)
#define print(m_what)  std::cout << (m_what)
#define println(m_what) std::cout << (m_what) << std::endl
#define FOR(i, N) for (int i = 0; i < N; i++)
template<typename... T> void read(T&... args) { ((std::cin >> args), ...); }
void read(vi& arr) { FOR(i, arr.size()) { std::cin >> arr[i]; } }

#define KICK_START() input(T); for (int t = 1; t <= T; t++) { std::cout << "Case #" << t << ": "; KickStart(); }
//void KickStart() {}

// Main ///////////////////////////////////////////////////////
int MAIN() {
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
	REDIRECT();
	//KICK_START();

	return 0;
}

// Tests ////////////////////////////////////////////////////////

#ifdef _TESTING
int TEST() {

	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

