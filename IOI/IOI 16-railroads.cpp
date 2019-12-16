#include "railroad.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;
typedef long long ll;

int trav[404040], din[404040], dout[404040];
vector<pair<int, pair<int, int>>> edges;

int cmp[404040];
int find(int a) {
    while (cmp[a] != a) cmp[a] = cmp[cmp[a]], a = cmp[a];
    return a;
}
void onion(int a, int b) { cmp[find(a)] = cmp[find(b)]; }

ll plan_roller_coaster(vector<int> s, vector<int> t) {
    int n = s.size();

    FOR(i, 0, n) {
        trav[i * 2] = s[i];
        trav[i * 2 + 1] = t[i];
    }
    trav[2 * n] = 1;
    trav[2 * n + 1] = 2e9;

    sort(trav, trav + 2 * n + 2);
    FOR(i, 0, 2 * n + 2) cmp[i] = i;

    FOR(i, 0, n) {
        s[i] = lower_bound(trav, trav + 2 * n + 2, s[i]) - trav;
        t[i] = lower_bound(trav, trav + 2 * n + 2, t[i]) - trav;

        din[t[i]]++;
        dout[s[i]]++;
        onion(t[i], s[i]);
    }
    din[0]++;
    dout[2 * n + 1]++;
    onion(0, 2 * n + 1);

    ll ans = 0, sm = 0;
    FOR(i, 0, 2 * n + 1) {
        sm += dout[i] - din[i];
        if (sm < 0)
            onion(i, i + 1);
        else if (sm == 0)
            edges.push_back({trav[i + 1] - trav[i], {i, i + 1}});
        else {
            ans += sm * (trav[i + 1] - trav[i]);
            onion(i, i + 1);
        }
    }

    sort(edges.begin(), edges.end());
    for (auto& i : edges) {
        if (find(i.second.first) != find(i.second.second)) {
            onion(i.second.first, i.second.second);
            ans += i.first;
        }
    }

    return ans;
}
