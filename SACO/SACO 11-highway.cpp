#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int c[10101];
int find(int a) {
    while (c[a] != a) c[a] = c[c[a]], a = c[a];
    return a;
}
void onion(int a, int b) { c[find(a)] = c[find(b)]; }

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n + 1) c[i] = i;
    FOR(i, 0, m) {
        int a, b;
        cin >> a >> b;
        if (find(1) != find(b) && find(a) == find(1)) {
            cout << "YES\n";
            onion(a, b);
        } else cout << "NO\n";
    }
    return 0;
}