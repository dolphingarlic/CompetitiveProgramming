#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m, k;
set<pair<int, int>> cuts[100], edges;
vector<set<pair<int, int>>> fin;
int mx;

void solve(int level, int l, int r) {
    if (l == r) return;

    int mid = (l + r) / 2;
    for (pair<int, int> i : edges) {
        if (i.first >= l && i.second <= r &&
            i.first <= mid && i.second > mid) {
            cuts[level].insert(i);
            edges.erase(i);
        }
    }
    solve(level + 1, l, mid);
    solve(level + 1, mid + 1, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    FOR(i, 0, m) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        edges.insert({a, b});
    }

    solve(0, 1, n);

    FOR(i, 0, 100) if (cuts[i].size()) fin.push_back(cuts[i]);

    cout << fin.size() << '\n';
    for (auto& i : fin) {
        cout << i.size() << '\n';
        for (pair<int, int> j : i)
            cout << j.first << ' ' << j.second << '\n';
    }
    return 0;
}