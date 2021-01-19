/*
SACO 2021 Rocket Shipyard 2
- Binary search on the answer: if we can achieve X days, we can also achieve X + 1 days
- Assume WLOG that P > Q
- For X days, we can check the minimum total number of times we need to allocate a P factory
- If this number is at no greater than KX, then X is good
- Complexity: O(N log M)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll n, k, p, q, a[100000];

bool check(ll days) {
    ll p_needed = 0;
    for (int i = 0; i < n; i++) {
        if (p * days < a[i]) return false;
        p_needed += (a[i] - q * days - 1) / p + 1;
    }
    return p_needed <= days * k;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k >> p >> q;
    if (p < q) swap(p, q), k = n - k;
    for (int i = 0; i < n; i++) cin >> a[i];
    
    ll l = 1, r = accumulate(a, a + n, 0);
    while (l != r) {
        ll mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l;
}
