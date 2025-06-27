class Solution {
public:
    string longestSubsequenceRepeatedK(string s, int k) {
        unordered_map<int, int> freq;
        // Count frequency of each character
        for (auto ch: s){
            freq[ch]++;
        }
        set<char, greater<char>> candidates;    //We needed lexicographically largest string, and this is taken care by this step
        // Keep characters with freq ≥ k
        for (auto [key, val]: freq){
            if (val>=k) candidates.insert(key);
        }

        if (candidates.size()==0) return "";

        queue<string> q;
        // Start BFS with single-character strings
        for (auto ch: candidates){
            q.push(string(1, ch));  // string(1, ch) converts a character into a string of len 1
        }

        // //THIS POINT ONWARDS WE COULD HAVE USED A MODIFIED string s WHICH CONTAINS ONLY 
        // //THE CHARACTERS WITH FREQ>=k BCZ ALL OTHER WONT BE USEFUL;
        // //This saves time further
        // string tmp;
        // for (auto ch: s){
        //     if (candidates.find(ch)!=candidates.end()) tmp+=ch;
        // }
        // s=tmp;

        string ans=string(1, *candidates.begin());  //// Initialize answer with lexicographically largest single char string
        int maxSize=0;
        while(!q.empty()){
            string curr=q.front();
            q.pop();
            for (auto ch: candidates){
                string tmp=curr+ch;
                if (isValidSubsequence(tmp, s, k)){ //// Check if tmp*k is subsequence of s
                    q.push(tmp);
                    if (tmp.size()>maxSize){
                        ans=tmp;
                        maxSize=tmp.size();
                    }
                }
            }
        }
        return ans;
    }
    bool isValidSubsequence(string tmp, string s, int k){
        //This fns return true if (tmp*k) is a valid subsequence of s
        int i=0;
        string subsequence;
        for (int i=0; i<k; i++){
            subsequence+=tmp;
        }
        int j=0;
        for (int i=0; i<s.size(); i++){
            if (s[i]==subsequence[j]) j++;
            if (j==subsequence.size()) return true;
        }
        return false;
    }
};