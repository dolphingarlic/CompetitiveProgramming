/*
JOISC 2017 Port Facility
- Let each shipment be a node and draw an edge between 2 nodes if they can't be in the same dock
- Notice how there is an edge between A and B iff the starts and ends are like A--B--A--B
    - To construct these edges, we can use a set
- Notice how it is possible to handle the shipments iff the resulting graph is bipartite
    - If it is bipartite, the answer is simply 2^(Number of connected components)
- To check whether the graph is bipartite, we use DSU
    - Instead of just unioning A and B, union A with B + N and A + N with B
    - If find(A) == find(A + N), there is an odd cycle and therefore the graph isn't bipartite
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

pair<int, int> a[1000000];
int cmp[2000000], n;

int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

void onion(int A, int B) { cmp[find(A)] = find(B); }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    FOR(i, 0, n) cin >> a[i].first >> a[i].second;
    sort(a, a + n);

    iota(cmp, cmp + 2 * n, 0);

    set<pair<int, int>> s;
    FOR(i, 0, n) {
        while (s.size() && (*s.begin()).first < a[i].first) s.erase(s.begin());

        auto ub = s.upper_bound({a[i].second, n});
        if (ub != s.begin())
            for (ub--;; ub--) {
                onion(i, (*ub).second + n);
                onion(i + n, (*ub).second);
                if (find((*ub).second) == find((*s.begin()).second)) break;
                if (ub == s.begin()) break;
            }
        s.insert({a[i].second, i});
    }

    FOR(i, 0, n) if (find(i) == find(i + n)) return cout << 0, 0;
    ll cnt = 0, ans = 1;
    FOR(i, 0, 2 * n) if (find(i) == i) cnt++;
    FOR(i, 0, cnt / 2) ans = (ans * 2) % MOD;
    cout << ans;
    return 0;
}