/*
CEOI 2011 Matching
- KMP + some magical comparison function
- Consult "Looking For A Challenge?" for more details
- Complexity: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;

int p[N], h[N], pos[N], prv[N], nxt[N], l_pred[N], l_succ[N], partial[N];
vector<int> matches;

inline bool can_extend(int i, int j, int *v) {
    return ((!l_pred[j + 1] || v[i - l_pred[j + 1]] < v[i]) && (!l_succ[j + 1] || v[i] < v[i - l_succ[j + 1]]));
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        p[x - 1] = i;
        pos[i] = x - 1;
        prv[i] = i - 1, nxt[i] = i + 1;
    }
    for (int i = 0; i < m; i++) scanf("%d", h + i);

    for (int i = n - 1; ~i; i--) {
        if (~prv[p[i]]) {
            l_pred[i] = i - pos[prv[p[i]]];
            nxt[prv[p[i]]] = nxt[p[i]];
        }
        if (nxt[p[i]] != n) {
            l_succ[i] = i - pos[nxt[p[i]]];
            prv[nxt[p[i]]] = prv[p[i]];
        }
    }

    for (int i = 1, j = partial[0] = -1; i < n; i++) {
        while (~j && !can_extend(i, j, p)) j = partial[j];
        if (can_extend(i, j, p)) j++;
        partial[i] = j;
    }

    for (int i = 0, j = -1; i < m; i++) {
        while (~j && !can_extend(i, j, h)) j = partial[j];
        if (can_extend(i, j, h)) j++;
        if (j == n - 1) {
            matches.push_back(i - n + 2);
            j = partial[j];
        }
    }

    printf("%d\n", matches.size());
    for (int i : matches) printf("%d ", i);
    printf("\n");
    return 0;
}