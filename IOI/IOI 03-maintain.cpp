#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

set<pair<int, pair<int, int>>> s;
int component[201];

int fund(int a) {
    while (a != component[a]) component[a] = component[component[a]], a = component[a];
    return a;
}
int onion(int a, int b) { component[fund(a)] = component[fund(b)]; }

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, w;
    cin >> n >> w;

    FOR(i, 0, w) {
        int a, b, c;
        cin >> a >> b >> c;
        s.insert({c, {a, b}});

        FOR(j, 1, n + 1) component[j] = j;

        int ans = 0, cnt = 0;
        for (pair<int, pair<int, int>> i : s) {
            if (fund(i.second.first) != fund(i.second.second)) {
                cnt++, ans += i.first;
                onion(i.second.first, i.second.second);
            }
        }

        if (cnt != n - 1) cout << -1 << endl;
        else cout << ans << endl;
    }
    return 0;
}