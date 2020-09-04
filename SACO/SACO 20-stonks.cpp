#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

multiset<ll> buckets[30];
ll bsum[30];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q, tot = 0;
    cin >> q;
    while (q--) {
        char c;
        ll x;
        cin >> c >> x;
        int p = 31 - __builtin_clz(x), ans = 0;
        if (c == '+') buckets[p].insert(x), bsum[p] += x, tot++;
        else buckets[p].erase(buckets[p].find(x)), bsum[p] -= x, tot--;
        ll sm = 0;
        for (int i = 0; i < 30; i++) if (buckets[i].size()) {
            if (*buckets[i].begin() > 2 * sm) ans++;
            sm += bsum[i];
        }
        cout << tot - ans << '\n';
    }
    return 0;
}