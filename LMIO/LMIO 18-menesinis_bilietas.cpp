/*
LMIO 2018 Menesinis Bilietas
- DSU
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int cmp[500001], cmp_cnt;
set<int> graph[500001];

int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

void onion(int A, int B) {
    if (find(A) == find(B)) return;
    cmp[find(A)] = find(B);
    cmp_cnt--;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    iota(cmp, cmp + n + 1, 0);
    cmp_cnt = n;
    vector<pair<int, int>> bus;
    while (m--) {
        int u, v;
        char t;
        cin >> u >> v >> t;
        if (t == 'A') bus.push_back({u, v});
        else onion(u, v);
    }
    for (pair<int, int> i : bus) {
        if (find(i.first) == find(i.second)) continue;
        graph[find(i.first)].insert(find(i.second));
        graph[find(i.second)].insert(find(i.first));
    }

    int ans = 0;
    FOR(i, 1, n + 1) if (graph[find(i)].size() == cmp_cnt - 1) ans++;
    cout << ans;
    return 0;
}