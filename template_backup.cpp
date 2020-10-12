
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

typedef std::vector<int> ivec;
typedef std::vector<ivec> ivec2d;
typedef std::string string;
typedef long long ll;

template<typename... T> void read(T&... args) { ((std::cin >> args), ...); }
#define input(...) int __VA_ARGS__; read(__VA_ARGS__)
#define print(m_what)  std::cout << (m_what)
#define println(m_what) std::cout << (m_what) << std::endl
#define FOR(i, N) for (int i = 0; i < N; i++)

#define MOD (1e9 + 7)
#define MOD_ADD(a, b, mod) ((((a) % (mod)) + ((b) % (mod))) % (mod))
#define MOD_MUL(a, b, mod) ((((a) % (mod)) * ((b) % (mod))) % (mod))

#define KICK_START() input(T); for (int t = 1; t <= T; t++) { std::cout << "Case #" << t << ": "; KickStart(); }
//void KickStart() {}
using namespace std;


void KickStart() {

}

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
	TEST_MAIN(R"()", R"()");

	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING



// -- leetcode ---------------------------------------------------------------------------------------------------



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

#define input(m_type, m_name) m_type m_name; std::cin >> m_name
#define print(m_what)  std::cout << (m_what)
#define println(m_what) std::cout << (m_what) << std::endl
#define FOR(i, N) for (int i = 0; i < N; i++)

typedef std::vector<int> ivec;
typedef std::vector<ivec> ivec2d;
typedef std::string string;
typedef long long ll;

// Solution /////////////////////////////////////////////////////



// Tests ////////////////////////////////////////////////////////
int main() {
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

	// CHECK_EQ(Solution(), );
	return 0;
}


