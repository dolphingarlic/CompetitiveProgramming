/*
PAIO 2020 Ninja Race 2 (not sure what the first ninja race was)
- We answer the queries offline because why not
- Our path will always be of the form
  a -> (v1 - 1) -> v1 -> (v2 - 1) -> v2 -> ... -> b
  where v1 < v2 < ...
- For each a, we can maintain the list of v using a monotone queue/deque
    - We basically mark the elements of v as "active" and the rest
      as "inactive"
    - We also use a BIT to quickly query range sums and stuff
    - See the code for more details
- Complexity: O((N + Q) log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, q;
ll h[100001], diff[100001], bit[100001], ans[100001];
vector<pair<int, int>> bckt[100001];

void update(int pos, ll val) {
    for (; pos <= n; pos += pos & (-pos)) bit[pos] += val;
}

ll query(int a, int b) {
    ll ans = 0;
    for (; b; b -= b & (-b)) ans += bit[b];
    for (a--; a; a -= a & (-a)) ans -= bit[a];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> q;
        for (int i = 1; i <= n; i++) {
            cin >> h[i];
            diff[i] = h[i] - h[i - 1];
            bckt[i].clear();
        }
        for (int i = 1; i <= q; i++) {
            int a, b;
            cin >> a >> b;
            bckt[a].push_back({b, i});
        }
        
        deque<int> qu;
        for (int i = n; i; i--) {
            while (qu.size() && h[i] >= h[qu.front()]) {
                update(qu.front(), -diff[qu.front()]);
                qu.pop_front();
            }
            for (pair<int, int> j : bckt[i]) {
                int pos = upper_bound(qu.begin(), qu.end(), j.first) - qu.begin() - 1;
                if (pos == -1) ans[j.second] = 0;
                else ans[j.second] = query(i, qu[pos]);
            }
            update(i, diff[i]);
            qu.push_front(i);
        }
        for (int i : qu) update(i, -diff[i]);

        for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
    }
    return 0;
}