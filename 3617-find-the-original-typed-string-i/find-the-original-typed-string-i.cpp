class Solution {
public:
    int possibleStringCount(string word) {
        int n = word.size();
        vector<pair<char, int> > groups;
        int i = 0;

        // Group characters and their counts
        while (i < n) {
            int j = i;
            while (j < n && word[j] == word[i]) {
                ++j;
            }
            groups.push_back({word[i], j - i});
            i = j;
        }

        // Count all unique reductions (only one group can be shortened)
        int total = 1; // original word
        for (auto [ch, count] : groups) {
            if (count > 1) {
                total += (count - 1);
            }
        }

        return total;
    }
};