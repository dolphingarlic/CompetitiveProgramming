#include <bits/stdc++.h>
#include "cave.h"
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
void exploreCave(int N) {
    int known[5000], D[5000], S[5000], T[5000];
    fill(known, known + N, -1);
    FOR(i, 0, N) {
        fill(S, S + N, 1);
        FOR(j, 0, i) S[D[j]] = known[j];
        // Find state of i-th gate
        int res = tryCombination(S);
        if (res <= i && res != -1) known[i] = 0;
        else known[i] = 1;
 
        // Binary search for D[i]
        int l = 0, r = N - 1;
        while (l != r) {
            int mid = (l + r) / 2;
            fill(T, T + N, 1 - known[i]);
            fill(T + l, T + mid + 1, known[i]);
            FOR(j, 0, i) T[D[j]] = known[j];
            int res = tryCombination(T);
            if (res <= i && res != -1) l = mid + 1;
            else r = mid;
        }
        D[i] = l;
    }
    int a[5001], b[5001];
    FOR(i, 0, N) {
        a[D[i]] = known[i];
        b[D[i]] = i;
    }
    answer(a, b);
}