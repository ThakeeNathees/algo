
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

template <typename T> using vec = std::vector<T>;
typedef long long ll;
typedef vec<int> ivec; typedef vec<ll> llvec;
typedef vec<ivec> ivec2d;

#define input(...) int __VA_ARGS__; read(__VA_ARGS__)
#define print(m_what)  std::cout << (m_what)
#define println(m_what) std::cout << (m_what) << std::endl
#define FOR(i, N) for (int i = 0; i < N; i++)
template<typename... T> void read(T&... args) { ((std::cin >> args), ...); }
void read(ivec& arr) { FOR(i, arr.size()) { std::cin >> arr[i]; } }


// Solution /////////////////////////////////////////////////////
using namespace std;

// Tests ////////////////////////////////////////////////////////

int main() {
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

	// declarations -------------------------------
	ivec arr, arr2; ivec2d arr2d; vec<string> sarr;
	int i = 0, j = 0, k = 0;
	string str, str2;
	// --------------------------------------------


	//CHECK_EQ(Solution(), );
	return 0;
}

