/*
COCI 2021 Pizza
- Just do it
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    set<int> a;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        a.insert(k);
    }
    int m, ans = 0;
    cin >> m;
    while (m--) {
        int b;
        cin >> b;
        bool good = true;
        for (int i = 0; i < b; i++) {
            int x;
            cin >> x;
            good &= a.find(x) == a.end();
        }
        ans += good;
    }
    cout << ans;
    return 0;
}
