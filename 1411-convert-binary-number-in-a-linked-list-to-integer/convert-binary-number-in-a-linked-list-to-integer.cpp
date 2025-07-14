class Solution {
public:
    int getDecimalValue(ListNode* head) {
        ListNode* temp = head;
        int count = 0;
        while(temp){
            count++;
            temp = temp->next;
        }

        temp = head;
        int ans = 0;
        while(temp){
            count--;
            int bit = temp->val;
            if(bit == 1){
                ans += (1<<count);
            }
            temp = temp->next;
        }

        return ans;
    }
};