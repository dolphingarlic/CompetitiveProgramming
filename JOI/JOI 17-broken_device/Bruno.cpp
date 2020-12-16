/*
JOISC 2017 Broken Device
- Map each triple of bits to some bits in X:
    - If no bits are broken, encode two bits
    - If one bit is broken, encode one bit
    - Otherwise, encode zero bits
- The following table works:
    000 -> Null
    100 -> 1
    010 -> 0
    110 -> 10
    001 -> 00
    101 -> 01
    011 -> 1
    111 -> 11
*/

#include "Brunolib.h"

long long Bruno(int N, int A[]) {
    long long ans = 0;
    for (int i = 0, j = 0; i < N; i += 3) {
        int hsh = A[i] + 2 * A[i + 1] + 4 * A[i + 2];
        switch (hsh) {
            case 1:
            case 6:
                ans += 1ll << j;
            case 2:
                j++;
                break;
            case 7:
                ans += 1ll << j;
            case 5:
                ans += 1ll << j + 1;
                j += 2;
                break;
            case 3:
                ans += 1ll << j;
            case 4:
                j += 2;
                break;
        }
    }
    return ans;
}