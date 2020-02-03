#include "prize.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> res[202020];
bool visited[202020];

int worst_sum = 0;

vector<int> query(int pos) {
    if (visited[pos]) return res[pos];
    visited[pos] = true;
    res[pos] = ask(pos);
    if (res[pos][0] + res[pos][1] == 0) throw pos;
    return res[pos];
}

void binary_search(int l, int r, int nl, int nr) {
    FOR(i, 0, r - l + 1) {
        int mid, midl = (l + r) / 2 - i / 2, midr = (l + r) / 2 + (i + 1) / 2;
        if (i & 1)
            mid = midr;
        else
            mid = midl;

        vector<int> x = query(mid);
        if (x[0] + x[1] == worst_sum) {
            int xl = (i & 1 ? midr - midl : 0), xr = (i & 1 ? 0 : midr - midl);
            if (x[0] - xl > nl) binary_search(l, midl - 1, nl, x[1] + xl);
            if (x[1] - xr > nr) binary_search(midr + 1, r, x[0] + xr, nr);
            break;
        }
    }
}

int find_best(int n) {
    try {
        int p = 0;
        for (int i = 0; i < 474 && i < n && worst_sum < 27; i++) {
            vector<int> x = query(i);
            if (x[0] + x[1] > worst_sum) p = i, worst_sum = x[0] + x[1];
        }
        binary_search(p, n - 1, p, 0);
    } catch (int ans) {
        return ans;
    }

    return -1;
}
