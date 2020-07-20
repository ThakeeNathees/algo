#pragma once

#include "../../algo.h"

// https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/

class Solution {
public:
    int numOfWays(int n)
    {
        vector<vector<long>> dp(n + 1, vector<long>(2, 0));
        int hell = 1000000007;
        //dp[i][0] is for ABC type pattern which will give 2 ABA type and 3 ABC type
        //dp[i][1] is for ABA type pattern which will give 2 ABA type and 2 ABC type
        dp[1][0] = 6, dp[1][1] = 6;
        for (int i = 2; i <= n; i++) {
            dp[i][0] = 3 * dp[i - 1][0] + 2 * dp[i - 1][1];
            dp[i][1] = 2 * dp[i - 1][0] + 2 * dp[i - 1][1];
            dp[i][0] = dp[i][0] % hell;
            dp[i][1] = dp[i][1] % hell;
        }
        int ans = (dp[n][0] + dp[n][1]) % hell;
        return ans;
    }
};