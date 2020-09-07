/*
EOI 2019 GCD
- There are a bunch of different cases where it's not possible (see code)
- Otherwise, just have N - 1 of G and one of S - (N - 1) * G
- Complexity: O(N) 
*/

#include <bits/stdc++.h>
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
        if ((n == 1 && s != g) || s % g != 0 || (n - 1) >= s / g) cout << "No\n";
        else {
            cout << "Yes\n";
            FOR(i, 1, n) cout << g << ' ';
            cout << s - (n - 1) * g << '\n';
        }
    }
    return 0;
}