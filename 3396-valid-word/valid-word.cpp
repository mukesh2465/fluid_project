class Solution {
public:
    bool isValid(string w) {
        if (w.size() < 3) return false;

        int v = 0, c = 0;
        std::bitset<128> vb;
        vb.set('a'); vb.set('e'); vb.set('i'); vb.set('o'); vb.set('u');
        vb.set('A'); vb.set('E'); vb.set('I'); vb.set('O'); vb.set('U');

        for (char ch : w) {
            if (!isalnum(ch)) return false;
            if (isalpha(ch)) {
                if (vb.test(ch))
                    v++;
                else
                    c++;
            }
        }

        return v && c;
    }
};