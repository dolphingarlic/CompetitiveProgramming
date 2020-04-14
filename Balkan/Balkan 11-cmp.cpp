/*
Balkan 2011 cmp
- Consider A and B in base 4
- First, encode each prefix of A (6 operations)
- Next, we use binary search to find the longest common prefix of A and B (3 operations)
    - If this prefix is of length 6, A == B
- Consider the digit directly after this prefix for B
    - If it is > 1, then we only need to check if pref * 4 + 3 is encoded
    - Otherwise, we only need to check if pref * 4 + 0 is encoded
    - Check whether it is and return the answer (1 operation)
- Total: At most 10 operations
*/

#include "cmp.h"

int delta[6]{1, 4097, 5121, 5377, 5441, 5457};

void remember(int n) {
    for (int i = 0; i < 6; i++) bit_set((n >> i * 2) + delta[i]);
}

int compare(int b) {
    int l = 0, r = 6;
    while (l != r) {
        int mid = (l + r) / 2;
        if (bit_get((b >> mid * 2) + delta[mid])) r = mid;
        else l = mid + 1;
    }

    if (!l) return 0;
    int last_digit = (b >> l * 2 - 2) & 3;
    if (last_digit > 1) {
        if (bit_get((((b >> l * 2) << 2) + 3) + delta[l - 1])) return -1;
        return 1;
    } else {
        if (bit_get(((b >> l * 2) << 2) + delta[l - 1])) return 1;
        return -1;
    }
}
