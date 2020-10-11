
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

bool is_subsequence(const string& s1, const string& s2) {
    int p = 0;
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] == s2[p]) {
            p++;
        }
        if (p == s2.size()) return true;
    }
    return false;
}

// Main ///////////////////////////////////////////////////////
int MAIN() {
    REDIRECT();
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

    input(string, s1);
    input(string, s2);

    int N = s1.size();

    FOR(i, N) {
        input(int, n);
        s1[--n] = '*';
        if (!is_subsequence(s1, s2)) {
            println(i);
            break;
        }
    }

    return 0;
}


// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {
    TEST_MAIN(R"(kkkbkkk
kbk
5 7 6 4 3 2 1)", R"(2)");


    // CHECK_EQ(Solution(), );
    // TEST_MAIN(R"()", R"()");
    return 0;
}
#endif // _TESTING

