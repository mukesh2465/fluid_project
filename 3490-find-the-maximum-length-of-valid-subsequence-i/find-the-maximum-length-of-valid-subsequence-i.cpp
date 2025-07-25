class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int allev = 0, allodd = 0, oddev = 0;

        // Count total even and odd numbers
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] % 2 == 0) {
                allev++;
            } else {
                allodd++;
            }
        }

        // Count longest alternating odd-even subsequence
        bool expectOdd = true;
        bool expectEven = true;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] % 2 == 0 && expectEven) {
                oddev++;
                expectEven = false;
                expectOdd = true;
            } else if (nums[i] % 2 != 0 && expectOdd) {
                oddev++;
                expectOdd = false;
                expectEven = true;
            }
        }

        return max({allev, allodd, oddev});
    }
};