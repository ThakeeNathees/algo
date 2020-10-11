
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

struct Node {
	int h = -1;
	ivec next;
};

void dfs(std::vector<Node>& tree, int current, int h, ivec& leaf) {
	if (tree[current].h != -1) return;
	tree[current].h = h;
	for (int n : tree[current].next) {
		dfs(tree, n, h + 1, leaf);
	}
	if (tree[current].next.size() == 1) {
		leaf.push_back(current);
	}

}

int MAIN() {
	REDIRECT();
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

	input(int, T);
	while (T--) {
		input(int, N); input(int, root_id); root_id--;
		std::vector<Node> tree(N);
		FOR(n, N-1) {
			input(int, j); input(int, k);
			tree[j-1].next.push_back(k-1);
			tree[k-1].next.push_back(j-1);
		}
		ivec leaf; bool done = false;
		dfs(tree, root_id, 0, leaf);

		for (auto l : leaf) {
			if (l == root_id) {
				println("Hitland");
				done = true;
				break;
			}
		}
		if (!done) {
			if (tree.size() % 2) {
				println("Stalind");
			} else {
				println("Hitland");
			}
		}

	}


	return 0;
}


// Tests ////////////////////////////////////////////////////////
#ifdef _TESTING
int TEST() {


	TEST_MAIN(R"(2
4 4
1 2
2 3
3 4
5 1
1 2
1 3
1 4
1 5)", R"(Hitland
Stalind)");


	TEST_MAIN(R"(1
6 3
1 2
2 3
3 4
3 5
4 6)", R"(Hitland)");

	// CHECK_EQ(Solution(), );
	// TEST_MAIN(R"()", R"()");
	return 0;
}
#endif // _TESTING

