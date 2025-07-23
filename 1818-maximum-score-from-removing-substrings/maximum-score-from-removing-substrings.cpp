class Solution {
public:
    // Removes all instances of (first + second) pairs and returns the score earned
    int removePairs(string& s, char first, char second, int reward) {
        string st; // simulate stack
        int score = 0;

        for (char ch : s) {
            // If we find the target pair (first followed by second), pop and earn reward
            if (!st.empty() && st.back() == first && ch == second) {
                st.pop_back();    // remove matched first character
                score += reward;  // add score
            } else {
                st.push_back(ch); // push current char
            }
        }

        s = st; // update s to leftover characters for next pass
        return score;
    }

    int maximumGain(string s, int x, int y) {
        int total = 0;

        // Greedily remove the more valuable pair first
        if (x > y) {
            total += removePairs(s, 'a', 'b', x); // remove "ab"
            total += removePairs(s, 'b', 'a', y); // remove "ba"
        } else {
            total += removePairs(s, 'b', 'a', y); // remove "ba"
            total += removePairs(s, 'a', 'b', x); // remove "ab"
        }

        return total;
    }
};