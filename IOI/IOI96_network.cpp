#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[101], reversed[101], stck;
set<int> in[101], out[101];
int sccs = 1, cmp[101];
bool visited[101];

void dfs1(int node) {
    visited[node] = true;
    for (int i : graph[node]) if (!visited[i]) dfs1(i);
    stck.push_back(node);
}

void dfs2(int node) {
    cmp[node] = sccs;
    for (int i : reversed[node]) if (!cmp[i]) dfs2(i);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> k;
        while (k) {
            graph[i].push_back(k);
            cin >> k;
        }
    }

    FOR(i, 1, n + 1) if (!visited[i]) dfs1(i);

    FOR(i, 1, n + 1) for (int j : graph[i]) reversed[j].push_back(i);

    while (stck.size()) {
        if (!cmp[stck.back()]) {
            dfs2(stck.back());
            sccs++;
        }
        stck.pop_back();
    }

    FOR(i, 1, n + 1) for (int j : graph[i]) if (cmp[i] != cmp[j]) {
        in[cmp[j]].insert(i);
        out[cmp[i]].insert(j);
    }

    int cnt1 = 0, cnt2 = 0;
    FOR(i, 1, sccs) {
        if (!in[i].size()) cnt1++;
        if (!out[i].size()) cnt2++;
    }

    if (sccs == 2) cout << "1\n0\n";
    else cout << cnt1 << '\n' << (cnt1 > cnt2 ? cnt1 : cnt2) << '\n';
    return 0;
}