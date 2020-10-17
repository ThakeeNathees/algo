
// Headers and Macros ////////////////////////////////////////
#ifdef _TESTING
	#define CPP_IMPL
	#include "include.h"
#else
	#include <bits/stdc++.h>
#endif

template <typename T> using vec = std::vector<T>;
typedef long long ll;
typedef vec<int> ivec; typedef vec<ll> llvec;
typedef vec<ivec> ivec2d;
using namespace std;
#define FOR(i, N) for (int i = 0; i < N; i++)

//////////////////////////////////////////////////////////////////

IvecDraw* darr;

int _partition(ivec& arr, int l, int r) {
	int pivot = arr[r - 1];
	int pivot_ind = l;
	darr->color_override[pivot_ind] = Color::D_YELLOW;

	for (int i = l; i < r - 1; i++) {
		if (arr[i] < pivot) {
			swap(arr[i], arr[pivot_ind++]);
			darr->color_override.erase(pivot_ind - 1);
			darr->color_override[pivot_ind] = Color::D_YELLOW;
		}
		draw("partition", (*darr)(l, r, i));
	}
	swap(arr[pivot_ind], arr[r - 1]);
	darr->color_override[pivot_ind] = Color::D_GREEN;
	draw("partition", (*darr)(pivot_ind));
	if (r == l + 2) darr->color_override[l] = Color::D_GREEN, darr->color_override[l + 1] = Color::D_GREEN;
	return pivot_ind;
}

void quick_sort(ivec& arr, int l = -1, int r = -1) {
	if (l == -1 && r == -1) l = 0, r = arr.size();
	if (l > r - 2) {
		darr->color_override[l] = Color::D_GREEN;
		return;
	}

	draw("quick sort", (*darr)(l, r));

	int pivot_index = _partition(arr, l, r);
	quick_sort(arr, l, pivot_index);
	quick_sort(arr, pivot_index + 1, r);
}

// Tests ////////////////////////////////////////////////////////

int main() {
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

	ivec arr; FOR(i, 20) arr.push_back(rand() % 100);
	DBG_IVEC(drarr, arr); darr = &drarr; //Globals::draw_pause = false;

	quick_sort(arr);
	draw("result", (*darr)());

	return 0;
}

