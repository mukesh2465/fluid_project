class Solution {
public:
    char kthCharacter(int k) {
        string s = "a";

        // Keep generating next parts until length is sufficient
        while (s.length() < k) {
            string next_part = "";
            for (char ch : s) {
                next_part += (char)(((ch - 'a' + 1) % 26) + 'a');
            }
            s += next_part;
        }

        return s[k - 1];
    }
};