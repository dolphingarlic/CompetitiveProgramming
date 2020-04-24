/*
POI 2011 Meteors
- Parallel binary search
- Imagine there was only 1 nation we had to query
    - We can binary search for the number of meteor showers needed and answer this in O((K + M) log K log M)
      by using a BIT for range updates and point queries
    - This turns into O(N(K + M) log K log M) if we have to query other nations, which is not ideal
- Notice how a single meteor shower affects the answer of all nations, so we can parallel binary search
- Complexity: O((K + M) log K log M)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m, l[300002], r[300002];
ll bit[300002], req[300002], num[300002];
pair<int, int> event[300002];
vector<int> owned[300002], to_check[300002];

void update(int pos, ll val) {
    for (; pos <= m; pos += (pos & (-pos))) bit[pos] += val;
}

ll query(int pos) {
    ll ans = 0;
    for (; pos; pos -= (pos & (-pos))) ans += bit[pos];
    return ans;
}

void update(pair<int, int> range, ll val) {
    if (range.first > range.second) update(1, val);
    update(range.first, val), update(range.second + 1, -val);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, m + 1) {
        int x;
        cin >> x;
        owned[x].push_back(i);
    }
    FOR(i, 1, n + 1) cin >> req[i];

    int k;
    cin >> k;
    FOR(i, 1, k + 1) cin >> event[i].first >> event[i].second >> num[i];

    FOR(i, 1, n + 1) l[i] = 1, r[i] = k + 1;
    bool done = false;
    while (!done) {
        done = true;

        fill(bit + 1, bit + m + 1, 0);
        FOR(i, 1, n + 1) if (l[i] != r[i]) to_check[(l[i] + r[i]) / 2].push_back(i);

        FOR(i, 1, k + 1) {
            update(event[i], num[i]);
            while (to_check[i].size()) {
                done = false;
                int nation = to_check[i].back();
                to_check[i].pop_back();

                ll tot = 0;
                for (int j : owned[nation]) {
                    tot += query(j);
                    if (tot >= req[nation]) break;
                }
                if (tot >= req[nation]) r[nation] = i;
                else l[nation] = i + 1;
            }
        }
    }

    FOR(i, 1, n + 1) {
        if (l[i] == k + 1) cout << "NIE\n";
        else cout << l[i] << '\n';
    }
    return 0;
}