class Solution {
public:
    // Helper to get sum of fruits between positions l to r
    int getSum(int l, int r, int maxPos, vector<int>& prefixSum) {
        if (l < 0)  l = 0;
        if (r >= maxPos) r = maxPos - 1;
        if (l > r) return 0;
        return prefixSum[r] - (l > 0 ? prefixSum[l - 1] : 0);
    }

    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        // Max position needed in the line (based on furthest fruit or possible max movement)
        int maxPos = max(fruits.back()[0], startPos + k) + 1;

        // Step 1: create fruit amount array
        vector<int> fruitAmount(maxPos, 0);
        for (auto& f : fruits) {
            fruitAmount[f[0]] = f[1];
        }

        // Step 2: compute prefix sum
        vector<int> prefixSum(maxPos, 0);
        prefixSum[0] = fruitAmount[0];
        for (int i = 1; i < maxPos; i++) {
            prefixSum[i] = prefixSum[i - 1] + fruitAmount[i];
        }

        // Step 3: Try all 4 movement patterns

        // Case 1: move only left from startPos
        int case1 = getSum(startPos - k, startPos, maxPos, prefixSum);

        // Case 2: move only right from startPos
        int case2 = getSum(startPos, startPos + k, maxPos, prefixSum);

        int case3 = 0;
        int case4 = 0;

        // Case 3 & 4: move both directions with turn in between
        for (int x = 1; x <= k; x++) {
            // Move x steps left, then turn and (k - 2x) steps right
            case3 = max(case3, getSum(startPos - x, startPos + (k - 2 * x), maxPos, prefixSum));

            // Move x steps right, then turn and (k - 2x) steps left
            case4 = max(case4, getSum(startPos - (k - 2 * x), startPos + x, maxPos, prefixSum));
        }

        // Final answer is max of all 4 strategies
        return max({case1, case2, case3, case4});
    }
};
