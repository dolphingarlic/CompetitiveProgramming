#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 1e18;

int n, q;
ll x[200002], pref[200002], ans[200002];
ll contrib[200002], bit[200002];
vector<pair<int, int>> bckt[200001];

void update(int pos, ll val) { for (; pos <= n; pos += pos & -pos) bit[pos] += val; }

ll query(int a, int b) {
    ll ans = 0;
    for (; b; b -= b & -b) ans += bit[b];
    for (a--; a; a -= a & -a) ans -= bit[a];
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        pref[i] = pref[i - 1] + x[i];
    }
    x[n + 1] = INF;
    pref[n + 1] = pref[n] + x[n + 1];
    for (int i = 1; i <= q; i++) {
        int a, b;
        cin >> a >> b;
        bckt[a].push_back({b, i});
    }
    deque<int> stck = {n + 1};
    for (int i = n; i; i--) {
        while (stck.size() && x[i] >= x[stck.front()]) {
            update(stck.front(), -contrib[stck.front()]);
            stck.pop_front();
        }
        contrib[i] = (stck.front() - 1 - i) * x[i] - (pref[stck.front() - 1] - pref[i]);
        update(i, contrib[i]);
        stck.push_front(i);
        for (pair<int, int> j : bckt[i]) {
            int pos = upper_bound(stck.begin(), stck.end(), j.first) - stck.begin() - 1;
            ans[j.second] = (pos ? query(i, stck[pos - 1]) : 0) + (j.first - stck[pos]) * x[stck[pos]] - (pref[j.first] - pref[stck[pos]]);
        }
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
    return 0;
}
