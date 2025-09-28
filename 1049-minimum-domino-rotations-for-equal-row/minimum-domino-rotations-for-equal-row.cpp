class Solution {
    int FindScore(const vector<int>& tops, const vector<int>& bottoms) {
        int val = tops.front();
        const int n = tops.size();

        int up = 0;
        int dn = 0;

        for (int i = 0; i < n; ++i) {
            if (tops[i] != val && bottoms[i] != val) {
                return -1;
            }
            up += tops[i] != val;
            dn += bottoms[i] != val;
        }
        return std::min(up, dn);
    }

public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {

        int rotations = FindScore(tops, bottoms);
        if (rotations == -1) {
            return FindScore(bottoms, tops);
        }
        return rotations;
    }
};