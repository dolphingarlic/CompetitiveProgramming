/*
CEOI 2011 Hotel
- Sort orders by price and assign each to the smallest room available
- Then just pick the O best order-room pairs
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

pair<ll, int> orders[500000];
multiset<pair<int, ll>> rooms;
priority_queue<ll> res;

int main() {
    int n, m, o;
    scanf("%d %d %d", &n, &m, &o);
    for (int i = 0; i < n; i++) {
        ll cost;
        int sz;
        scanf("%lld %d", &cost, &sz);
        rooms.insert({sz, cost});
    }
    for (int i = 0; i < m; i++) scanf("%lld %d", &orders[i].first, &orders[i].second);
    sort(orders, orders + m, greater<pair<ll, int>>());
    for (int i = 0; i < m; i++) {
        auto ptr = rooms.lower_bound({orders[i].second, LLONG_MIN});
        if (ptr == rooms.end()) continue;
        res.push(orders[i].first - (*ptr).second);
        rooms.erase(ptr);
    }

    ll ans = 0;
    for (int i = 0; i < o; i++) {
        if (!res.size() || res.top() < 0) break;
        ans += res.top();
        res.pop();
    }
    printf("%lld\n", ans);
    return 0;
}