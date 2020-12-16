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

#include "Annalib.h"

void set(int p, int x) { for (int i = 0; i < 3; i++) Set(p + i, (x >> i) & 1); }

void Anna(int N, long long X, int K, int P[]) {
    bool B[150];
    for (int i = 0; i < N; i++) B[i] = false;
    for (int i = 0; i < K; i++) B[P[i]] = true;

    for (int i = 0, j = 0; i < N; i += 3) {
        if (j > 62 || B[i] + B[i + 1] + B[i + 2] > 1) set(i, 0);
        else if ((!B[i] && !B[i + 1] && !B[i + 2]) || (B[i + 1] && !(X & (1ll << j)))) {
            if (X & (1ll << j)) {
                if (X & (1ll << j + 1)) set(i, 7);
                else set(i, 3);
            } else {
                if (X & (1ll << j + 1)) set(i, 5);
                else set(i, 4);
            }
            j += 2;
        } else {
            if (!(X & (1ll << j))) set(i, 2);
            else if (B[i]) set(i, 6);
            else set(i, 1);
            j++;
        }
    }
}