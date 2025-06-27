class Solution {
public:
    string ans = "";
    bool isSubsequence(string &s, string &temp) {
        int i = 0;
        for(auto &ch : s) {
            if(i < temp.size() && ch == temp[i]) ++i;
        }
        return i == temp.size();
    }
    bool check(string &s, string &temp, int k) {
        string repeated = "";
        for(int i = 0; i < k; ++i) repeated += temp;
        return isSubsequence(s, repeated);
    }
    void solve(string &s, string &temp, int k) {
        for(auto ch = 'z'; ch >= 'a'; --ch) {
            temp.push_back(ch);
            if(check(s, temp, k)) {
                // pick lexicographically greatest
                if(temp.size() > ans.size() ||
                (temp.size() == ans.size() && temp > ans)) ans = temp;

                solve(s, temp, k);
            }
            temp.pop_back(); // backtrack
        }
    }
    string longestSubsequenceRepeatedK(string s, int k) {
        string temp = "";
        solve(s, temp, k);
        return ans;
    }
};