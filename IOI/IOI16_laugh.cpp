#include "laugh.h"

int longest_laugh(std::string s) {
    int ans = 0, curr = 0;
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] == 'a' && (i == 0 || s[i - 1] == 'h')) || (s[i] == 'h' && (i == 0 || s[i - 1] == 'a'))) curr++;
        else if (s[i] == 'a' || s[i] == 'h') curr = 1;
        else curr = 0;
        ans = (ans > curr ? ans : curr);
    }
    return ans;
}
