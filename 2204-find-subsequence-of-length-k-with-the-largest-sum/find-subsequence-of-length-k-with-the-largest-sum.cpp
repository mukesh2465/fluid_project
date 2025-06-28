class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        int n = nums.size();
        vector<pair<int, int>> arr;

        // Step 1: Store value and index
        for (int i = 0; i < n; ++i) {
            arr.push_back({nums[i], i});
        }

        // Step 2: Sort descending by value
        sort(arr.begin(), arr.end(), [](auto &a, auto &b) {
            return a.first > b.first;
        });

        // Step 3: Sort top-k by index
        sort(arr.begin(), arr.begin() + k, [](auto &a, auto &b) {
            return a.second < b.second;
        });

        // Step 4: Collect values
        vector<int> res;
        for (int i = 0; i < k; ++i) {
            res.push_back(arr[i].first);
        }
        return res;
    }
};