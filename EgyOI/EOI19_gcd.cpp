#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q;
    cin >> q;
    while (q--) {
        ll n, s, g;
        cin >> n >> s >> g;
        if ((n == 1 && s != g) || s % g != 0 || (n - 1) * g >= s) cout << "No\n";
        else {
            cout << "Yes\n";
            FOR(i, 1, n) cout << g << ' ';
            cout << s - (n - 1) * g << '\n';
        }
    }
    return 0;
}