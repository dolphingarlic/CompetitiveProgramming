/*
LMiO 2017 Faktai
- Bitmask stuff
*/

#include <bits/stdc++.h>
using namespace std;

bitset<200> bs[20];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            int f;
            scanf("%d", &f);
            bs[f - 1][i] = 1;
        }
    }

    int lb = n, ub = 0;
    for (int mask = 0; mask < (1 << m); mask++) {
        bitset<200> cov;
        bool good = true;
        for (int i = 0; i < m; i++) if (mask & (1 << i)) {
            if ((cov & bs[i]).count()) {
                good = false;
                break;
            }
            cov |= bs[i];
        }
        if (good && cov.count() == n) {
            lb = min(lb, __builtin_popcount(mask));
            ub = max(ub, __builtin_popcount(mask));
        }
    }
    printf("%d %d", lb, ub);
    return 0;
}