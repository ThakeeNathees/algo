
// Headers ////////////////////////////////////////////////////
#include <limits.h>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <cmath>

#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>

// Macros //////////////////////////////////////////////////////
#ifdef _TESTING
	#define CPP_IMPL
	#include "include.h"
#else
	#define MAIN main
	#define REDIRECT()
#endif

typedef std::vector<int> ivec;
typedef std::vector<ivec> ivec2d;
typedef std::string string;
typedef std::vector<string> svec;
typedef long long ll;

#define input(m_type, m_name) m_type m_name; std::cin >> m_name
#define print(m_what)  std::cout << (m_what)
#define println(m_what) std::cout << (m_what) << std::endl
#define array_erase(m_arr, m_elem) (m_arr).erase(std::find((m_arr).begin(), (m_arr).end(), (m_elem)))

#define EOL() do { std::string _line; std::getline(std::cin, _line); } while (false)
#define FOR(i, N) for (int i = 0; i < N; i++)
#define FORL(i, m_begin, m_end) for (int i = m_begin; i < m_end; i++)

#define MOD (1e9 + 7)
#define MOD_ADD(a, b, mod) ((((a) % (mod)) + ((b) % (mod))) % (mod))
#define MOD_MUL(a, b, mod) ((((a) % (mod)) * ((b) % (mod))) % (mod))

#define KICK_START() input(int, T); for (int t = 1; t <= T; t++) { std::cout << "Case #" << t << ": "; KickStart(); }
//void KickStart() { print(ans); }

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

	// CHECK_EQ(Solution(), );
	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

