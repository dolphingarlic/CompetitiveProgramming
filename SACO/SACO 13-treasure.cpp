#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int s, p;
    cin >> s >> p;
    while ((p - 1) / 2 >= s) {
        cout << "0\n";
        p--;
    }
    cout << s - (p - 1) / 2 << '\n';
    FOR(i, 0, p - 1) cout << (i & 1) << '\n';
    return 0;
}