

#define ALGO_DEBUG 1
#define TEST_RUNS 10
#include "algo.h"

#include "src/z_function.h"

#include "src/dp/knapsack.h"
#include "src/dp/cutting_rod.h"
#include "src/dp/max_product.h"

int main() {
	// TO USE UNICODE:
	//_setmode(_fileno(stdout), _O_U16TEXT);
	//_setmode(_fileno(stdin), _O_U16TEXT);

	RUN(max_product(10));

	return 0;
}
