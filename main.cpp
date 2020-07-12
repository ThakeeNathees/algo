

#define ALGO_DEBUG 1
#define TEST_RUNS 10
#define print(x) std::cout << (x) << std::endl
#include "algo.h"

// https://www.geeksforgeeks.org/dynamic-programming/


#include <stdio.h>
#include <memory.h>


int gcd(int a, int b) {
    while (a != 0 && b != 0) {
        if (a > b) a %= b;
        else b %= a;
    }
    if (a == 0) return b;
    return a;
}


int main() {

    return 0;
}