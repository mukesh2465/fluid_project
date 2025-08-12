class Solution {
private:
    int solve(int idx, int target, vector<int>& powers, vector<vector<int>>& dp, const int MOD) {
        if (target == 0) return 1;
        if (idx >= powers.size() || target < 0) return 0;
        if (dp[idx][target] != -1) return dp[idx][target];

        long long take = 0;
        if (powers[idx] <= target)
            take = solve(idx + 1, target - powers[idx], powers, dp, MOD);

        long long notTake = solve(idx + 1, target, powers, dp, MOD);

        return dp[idx][target] = (take + notTake) % MOD;
    }
public:
    int numberOfWays(int n, int x) {
        const int MOD = 1e9 + 7;

        vector<int> powers;
        for (int i = 1;; i++) {
            long long val = pow(i, x);
            if (val > n) break;
            powers.push_back(val);
        }

        int m = powers.size();
        vector<vector<int>> dp(m, vector<int>(n + 1, -1));

        return solve(0, n, powers, dp, MOD);
    }
};